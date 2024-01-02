# jump to program entry point
push _start
ldm.q r4, [sp]
pop r11
push r4
pop ip

read_input:
# read(0, inp_addr, 128)
pop r3	# add sp, 8
pop r4
pop r3
push 0
pop r3
push 128
pop r5
push 1
pop r2
syscall r9
push 0xdeadbeef	# secret_key
push validate_key
pop r5
jmp r5, sp, 0

key_string:
.string "Key:"

print_prompt:
# write(1, "Key:", 4)
spup
spup
push 4
push key_string
push 1
push 2
pop r2
pop r3
pop r4
pop r5
syscall r11
push read_input
ldm.q ip, [sp]

validate_key:
pop r7	# r7 = secret_key
push 0
pop r9
push r7
push r10
xor r10	# r10 = secret_key ^ code_key

# calculate fibonacci(728)
push 0
pop r14
spup
push 1
add r15
spup
pop r9

fib_loop_begin:
push fib_loop_end
pop r13
je r13 r9 728

fib_loop_end:


xor_loop_begin:
push xor_loop_end
pop r14
je r14 r9 128

push 8

push 0x20000	# inp_addr
push r9
add r4
ldm.q r5, [r4]
push r5
push r10
xor r5
stm.q [r4], r5

push r9
add r9

push xor_loop_begin
pop r14
jmp r14 ip 0xbd7f
xor_loop_end:

_start:
# write(1, "Hi!\n", 4)
push 4
push hi_string
push 1
push 2
pop r2
pop r3
pop r4
pop r5
push print_prompt	# this will be later popped into ip
push 0x20000	# inp_addr
syscall sp	# sp = 4
pop r10	# r10 = code_key = ????? TODO
push 0x40000	# TODO: adjust with MEM_SIZE in emulator.c
pop sp	# fix sp again
spup
pop ip	# jump to read_input

hi_string:
.string "Welcome!\n"

