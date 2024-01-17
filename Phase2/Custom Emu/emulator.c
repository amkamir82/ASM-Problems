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
"\x30\x51\x01\x00\x00\x00\x00\x00\x00\x53\x41\x1b\x04\x10\x13\x14\x13\x30\x00\x00\x00\x00\x00\x00"
"\x00\x00\x13\x30\x32\x00\x00\x00\x00\x00\x00\x00\x15\x30\x01\x00\x00\x00\x00\x00\x00\x00\x12\x29"
"\x30\xef\xbe\xad\xde\x00\x00\x00\x00\x30\x90\x00\x00\x00\x00\x00\x00\x00\x15\x60\x51\x00\x00\x00"
"\x00\x00\x00\x00\x00\x4b\x65\x79\x3a\x70\x70\x30\x04\x00\x00\x00\x00\x00\x00\x00\x30\x4d\x00\x00"
"\x00\x00\x00\x00\x00\x30\x01\x00\x00\x00\x00\x00\x00\x00\x30\x02\x00\x00\x00\x00\x00\x00\x00\x12"
"\x13\x14\x15\x2b\x30\x0e\x00\x00\x00\x00\x00\x00\x00\x53\x01\x43\x6f\x72\x72\x65\x63\x74\x21\x0a"
"\x17\x30\x00\x00\x00\x00\x00\x00\x00\x00\x19\x07\x0a\x42\x0a\x30\x00\x00\x00\x00\x00\x00\x00\x00"
"\x1e\x70\x30\x01\x00\x00\x00\x00\x00\x00\x00\x40\x0f\x70\x19\x30\xe7\x00\x00\x00\x00\x00\x00\x00"
"\x1d\x61\xd9\xd8\x02\x00\x00\x00\x00\x00\x00\x0f\x0e\x40\x0f\x70\x1e\x30\x01\x00\x00\x00\x00\x00"
"\x00\x00\x09\x40\x09\x30\xb7\x00\x00\x00\x00\x00\x00\x00\x10\x0a\x0f\x42\x0a\x30\x00\x00\x00\x00"
"\x00\x00\x00\x00\x19\x30\x3d\x01\x00\x00\x00\x00\x00\x00\x1e\x61\xe9\x20\x00\x00\x00\x00\x00\x00"
"\x00\x30\x08\x00\x00\x00\x00\x00\x00\x00\x30\x00\x00\x02\x00\x00\x00\x00\x00\x09\x40\x04\x53\x54"
"\x05\x0a\x42\x05\x51\x45\x09\x40\x09\x30\xf5\x00\x00\x00\x00\x00\x00\x00\x1e\x60\xe0\x72\xa6\x0d"
"\x00\x00\x00\x00\x00\x30\xa5\x01\x00\x00\x00\x00\x00\x00\x53\x01\x57\x72\x6f\x6e\x67\x21\x21\x21"
"\x0a\x30\x09\x00\x00\x00\x00\x00\x00\x00\x30\x9c\x01\x00\x00\x00\x00\x00\x00\x30\x01\x00\x00\x00"
"\x00\x00\x00\x00\x30\x02\x00\x00\x00\x00\x00\x00\x00\x12\x13\x14\x15\x30\xf8\xff\x03\x00\x00\x00"
"\x00\x00\x01\x1b\x30\x51\x00\x00\x00\x00\x00\x00\x00\x30\x00\x00\x02\x00\x00\x00\x00\x00\x21\x1a"
"\x53\x1b\x70\x10\x57\x65\x6c\x63\x6f\x6d\x65\x21\x0a\x30\x00\x00\x00\x00\x00\x00\x00\x00\x18\x70"
"\x19\x09\x30\x00\x00\x02\x00\x00\x00\x00\x00\x40\x0a\x53\xba\x0b\x30\x69\x2a\x04\x43\x7e\x54\x93"
"\x11\x42\x0d\x0d\x08\x40\x08\x30\x08\x00\x00\x00\x00\x00\x00\x00\x09\x40\x09\x09\x30\x00\x00\x02"
"\x00\x00\x00\x00\x00\x40\x0a\x53\xba\x0b\x30\x2d\x38\x37\x56\x11\x45\xfc\x0d\x42\x0d\x0d\x08\x40"
"\x08\x30\x08\x00\x00\x00\x00\x00\x00\x00\x09\x40\x09\x09\x30\x00\x00\x02\x00\x00\x00\x00\x00\x40"
"\x0a\x53\xba\x0b\x30\x2d\x6f\x5b\x5d\x52\x03\xc7\x20\x42\x0d\x0d\x08\x40\x08\x30\x08\x00\x00\x00"
"\x00\x00\x00\x00\x09\x40\x09\x09\x30\x00\x00\x02\x00\x00\x00\x00\x00\x40\x0a\x53\xba\x0b\x30\x6d"
"\x21\x5d\x70\x12\x52\xc5\x47\x42\x0d\x0d\x08\x40\x08\x30\x08\x00\x00\x00\x00\x00\x00\x00\x09\x40"
"\x09\x30\xa0\x02\x00\x00\x00\x00\x00\x00\x1e\x61\xe8\x00\x00\x00\x00\x00\x00\x00\x00\x30\x09\x00"
"\x00\x00\x00\x00\x00\x00\x30\x48\x01\x00\x00\x00\x00\x00\x00\x30\x01\x00\x00\x00\x00\x00\x00\x00"
"\x30\x02\x00\x00\x00\x00\x00\x00\x00\x12\x13\x14\x15\x26\x30\xc9\x02\x00\x00\x00\x00\x00\x00\x10"
"\x30\x09\x00\x00\x00\x00\x00\x00\x00\x30\x87\x00\x00\x00\x00\x00\x00\x00\x30\x01\x00\x00\x00\x00"
"\x00\x00\x00\x30\x02\x00\x00\x00\x00\x00\x00\x00\x12\x13\x14\x15\x26\x30\x00\x00\x00\x00\x00\x00"
"\x00\x00\x30\x03\x00\x00\x00\x00\x00\x00\x00\x12\x13\x24";

uint8_t *mem;
uint64_t reg[16];	// reg[0] = ip, reg[1] = sp

#ifdef DEBUG
void dump_debug_info(void) {

	// registers
	puts("registers: ");
	for (int i = 0; i < 16; i++) {
		printf("r%d = 0x%lx\n", i, reg[i]);
	}

	// inp_addr
	puts("inp_addr: ");
	for (int i = 0x20000; i < 0x20000 + 32; i++) {
		printf("%02x ", mem[i]);
	}
	putchar('\n');
}

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
				reg[0] += sizeof(uint64_t);
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
