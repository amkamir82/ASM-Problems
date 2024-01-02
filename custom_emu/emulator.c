#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

/*
instructions:
==============
push reg
push imm
pop reg
syscall reg => do syscall and return the result in reg
ldm.b reg1, [reg2] => reg1 = *(byte*)reg2
ldm.q reg1, [reg2] => reg1 = *(qword*)reg2
stm.b [reg1], reg2 => *(byte*)reg1 = reg2
stm.q [reg1], reg2 => *(qword*)reg1 = reg2
jcc reg1(addr), reg2, imm => jump to reg1 if (reg2 ? imm)
*/

#define MEM_SIZE 0x40000

uint8_t rom_img[] =
"\x30\x73\x00\x00\x00\x00\x00\x00\x00\x53\x41\x1b\x04\x10\x13\x14\x13\x30\x00\x00\x00\x00\x00\x00"
"\x00\x00\x13\x30\x28\x01\x00\x00\x00\x00\x00\x00\x15\x30\x01\x00\x00\x00\x00\x00\x00\x00\x12\x29"
"\x30\xef\xbe\xad\xde\x00\x00\x00\x00\x4b\x65\x79\x3a\x70\x70\x30\x04\x00\x00\x00\x00\x00\x00\x00"
"\x30\x39\x00\x00\x00\x00\x00\x00\x00\x30\x01\x00\x00\x00\x00\x00\x00\x00\x30\x02\x00\x00\x00\x00"
"\x00\x00\x00\x12\x13\x14\x15\x2b\x30\x0e\x00\x00\x00\x00\x00\x00\x00\x53\x01\x30\x04\x00\x00\x00"
"\x00\x00\x00\x00\x30\xbb\x00\x00\x00\x00\x00\x00\x00\x30\x01\x00\x00\x00\x00\x00\x00\x00\x30\x02"
"\x00\x00\x00\x00\x00\x00\x00\x12\x13\x14\x15\x30\x3d\x00\x00\x00\x00\x00\x00\x00\x30\x00\x00\x02"
"\x00\x00\x00\x00\x00\x21\x1a\x30\x00\x00\x04\x00\x00\x00\x00\x00\x11\x70\x10\x48\x69\x21\x0a";

uint8_t *mem;
uint64_t reg[16];	// reg[0] = ip, reg[1] = sp

void dump_debug_info(void) {
	for (int i = 0; i < 16; i++) {
		printf("r%d = 0x%lx\n", i, reg[i]);
	}
}

#ifdef DEBUG
void segfault_handler(int signum) {
	puts("SIGSEGV:");
	dump_debug_info();
	exit(1);
}
#endif	// DEBUG

void fatal(void) {
	fputs("Fatal error\n", stderr);
#ifdef DEBUG
	dump_debug_info();
#endif
	exit(1);
}

void clean_up(void)
{
	free(mem);
	exit(0);
}

void do_sys_read(uint8_t result_reg) {
	uint64_t fd = reg[3];
	uint64_t buf = reg[4];
	uint64_t size = reg[5];
	if (buf >= MEM_SIZE || size > MEM_SIZE || buf + size >= MEM_SIZE) {
		reg[result_reg] = -1;
		return;
	}
	reg[result_reg] = read(fd, mem + buf, size);
}

void do_sys_write(uint8_t result_reg) {
	uint64_t fd = reg[3];
	uint64_t buf = reg[4];
	uint64_t size = reg[5];
	if (buf >= MEM_SIZE || size > MEM_SIZE || buf + size >= MEM_SIZE) {
		reg[result_reg] = -1;
		return;
	}
	reg[result_reg] = write(fd, mem + buf, size);
}

void do_sys_rand(uint8_t result_reg) {
	reg[result_reg] = rand() % 0x10000;
}

// syscall number passed in reg[2]
// syscall args in reg[3], reg[4], reg[5], ...
void do_syscall(uint8_t result_reg)
{
	switch (reg[2]) {
		case 1:	// SYS_read
			do_sys_read(result_reg);
			break;
		case 2:	// SYS_write
			do_sys_write(result_reg);
			break;
		case 3:	// SYS_exit
			clean_up();
			break;
		case 4:	// SYS_rand
			do_sys_rand(result_reg);
			break;
		default:
			fatal();
			break;
	}
}

uint64_t do_pop(void) {
	reg[1] += 8;
	return *(uint64_t *)(mem + reg[1] - 8);
}

void do_pop_reg(uint8_t reg_idx) {
	reg[reg_idx] = do_pop();
}

void do_push_imm(uint64_t imm) {
	*(uint64_t *)(mem + reg[1] - 8) = imm;
	reg[1] -= 8;
}

void do_push_reg(uint8_t reg_idx) {
	do_push_imm(reg[reg_idx]);
}

void do_arithmetic_add(uint8_t result_reg) {
	reg[result_reg] = do_pop() + do_pop();
}

void do_arithmetic_sub(uint8_t result_reg) {
	reg[result_reg] = do_pop() - do_pop();
}

void do_arithmetic_xor(uint8_t result_reg) {
	reg[result_reg] = do_pop() ^ do_pop();
}

void do_arithmetic(uint8_t op, uint8_t result_reg) {
	switch (op) {
		case 0:	// add
			do_arithmetic_add(result_reg);
			break;
		case 1:	// sub
			do_arithmetic_sub(result_reg);
			break;
		case 2:	// xor
			do_arithmetic_xor(result_reg);
			break;
		default:
			fatal();
			break;
	}
}

void do_mem_access(uint8_t op, uint8_t dst_reg, uint8_t src_reg) {
	switch (op) {
		case 0:	// store byte
			mem[reg[dst_reg]] = (uint8_t)(reg[src_reg] & 0xff);
			break;
		case 1:	// store qword
			*(uint64_t *)(mem + reg[dst_reg]) = reg[src_reg];
			break;
		case 2:	// load byte
			reg[dst_reg] = mem[reg[src_reg]];
			break;
		case 3:	// load qword;
			reg[dst_reg] = *(uint64_t *)(mem + reg[src_reg]);
			break;
		default:
			fatal();
			break;
	}
}

void do_jmp(uint8_t op, uint8_t addr_reg, uint8_t cmp_reg, uint64_t imm) {
	switch (op) {
		case 0:	// jmp
			reg[0] = reg[addr_reg];
			break;
		case 1:	// je
			reg[0] = (reg[cmp_reg] == imm ? reg[addr_reg] : reg[0]);
			break;
		default:
			fatal();
			break;
	}
}

void do_sp_up(void) {
	reg[1] -= 8;
}

void execution_loop(void)
{
	while (1) {
		uint8_t op = mem[reg[0]++];
		uint8_t op_class = (op >> 4) & 0xf;

		uint8_t regs, result_reg;
		uint64_t imm;

		switch (op_class) {
			case 0:	// push reg
				do_push_reg(op & 0xf);
				break;
			case 1:	// pop reg
				do_pop_reg(op & 0xf);
				break;
			case 2:	// syscall reg
				do_syscall(op & 0xf);
				break;
			case 3:	// push imm
				imm = *(uint64_t *)(mem + reg[0]);
				reg[0] += sizeof(uint64_t);
				do_push_imm(imm);
				break;
			case 4:	// stack arithmetic
				result_reg = mem[reg[0]++];
				do_arithmetic(op & 0xf, result_reg);
				break;
			case 5:	// memory access
				regs = mem[reg[0]++];
				do_mem_access(op & 0xf, (regs >> 4) & 0xf, regs & 0xf);
				break;
			case 6: // jump
				regs = mem[reg[0]++];
				imm = *(uint64_t *)(mem + reg[0]);
				do_jmp(op & 0xf, (regs >> 4) & 0xf, regs & 0xf, imm);
				break;
			case 7:	// sp up
				do_sp_up();
				break;
			default:
				fatal();
				break;
		}
	}
}

void setup(void)
{
#ifdef DEBUG
	struct sigaction sa = {.sa_handler = segfault_handler};
	sigaction(SIGSEGV, &sa, NULL);
#endif
	srand(time(NULL));
	mem = malloc(MEM_SIZE);
	memcpy(mem, rom_img, sizeof(rom_img));	// TODO: replace with loop?
	reg[0] = 0;
	reg[1] = MEM_SIZE;
}

int main(void)
{
	setup();
	execution_loop();
	clean_up();
	return 0;
}
