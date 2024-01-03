#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <seccomp.h>
#include <assert.h>

#define SHELLCODE_LENGTH 0x80

#ifdef DEBUG
void hexdump(unsigned char *ptr, size_t size)
{
	fprintf(stderr, "\nhexdump @ %p:\n", ptr);
	for (size_t i = 0; i < size;) {
		fprintf(stderr, "%p:   ", ptr + i);
		size_t j;
		for (j = i; j - i < 16 && j < size; j++) {
			fprintf(stderr, "%02x ", ptr[j]);
		}
		fprintf(stderr, "   ");
		for (j = i; j - i < 16 && j < size; j++) {
			if (0x20 <= ptr[j] && ptr[j] < 0x7f)
				fputc(ptr[j], stderr);
			else
				fputc('.', stderr);
		}
		fputc('\n', stderr);
		i = j;
	}
}
#else
void hexdump(unsigned char *ptr, size_t size) {}
#endif	// DEBUG

void check_limits(unsigned char *shellcode, size_t size)
{
	// for (size_t i = 0; i < size; i++) {
	// 	if (shellcode[i] == 'H') {
	// 		puts("bad");
	// 		exit(1);
	// 	}
	// }
}

void make_changes(unsigned char *shellcode, size_t size)
{
	uint32_t *arr = (uint32_t *)shellcode;
	size_t arr_size = size / sizeof(uint32_t);
	for (size_t i = 0; i < arr_size; i++) {
		for (size_t j = i + 1; j < arr_size; j++) {
			if (arr[i] < arr[j]) {
				uint32_t tmp = arr[j];
				arr[j] = arr[i];
				arr[i] = tmp;
			}
		}
	}
}

void init_sandbox(void)
{
	// TODO: prevent open(..., O_WRONLY) or chroot to /tmp
	scmp_filter_ctx ctx;
	ctx = seccomp_init(SCMP_ACT_KILL);
	assert(ctx != NULL);
	assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0) == 0);
	assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0) == 0);
	assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0) == 0);
	assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 0) == 0);
	assert(seccomp_load(ctx) == 0);
}

void run_shellcode(unsigned char *shellcode, size_t size)
{
	unsigned char *code_ptr = mmap(0, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC,
									MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	assert(code_ptr != MAP_FAILED);
	memset(code_ptr, 0, 0x1000);
	memcpy(code_ptr, "\x31\xC0\x31\xF6\x31\xD2\x31\xFF", 8);
	memcpy(code_ptr + 8, shellcode, size);
	hexdump(code_ptr, size);
	init_sandbox();
	((void (*)())code_ptr)();
}

void disable_io_buffering(void)
{
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
}

int main(void)
{
	disable_io_buffering();
	
	unsigned char shellcode[SHELLCODE_LENGTH] = {};
	read(0, shellcode, sizeof(shellcode));
	
	check_limits(shellcode, sizeof(shellcode));
	make_changes(shellcode, sizeof(shellcode));
	run_shellcode(shellcode, sizeof(shellcode));
	return 0;
}
