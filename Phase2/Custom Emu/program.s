# flag = w3ll_d0n3!_y0u_r3v3rs3d_s85_3bf8

# encrypted flag
# 69 2a 04 43 7e 54 93 11 2d 38 37 56 11 45 fc 0d 2d 6f 5b 5d 52 03 c7 20 6d 21 5d 70 12 52 c5 47

# jump to program entry point
push _start
ldm.q r4, [sp]
pop r11
push r4
pop ip

read_input:
# read(0, inp_addr, 32)
pop r3	# add sp, 8
pop r4
pop r3
push 0
pop r3
push 32
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

success_string:
.string "Correct!\n"

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

push r15
push r14
add r15
spup
pop r14

push 1
push r9
add r9

push fib_loop_begin
pop ip
fib_loop_end:

push r10
push r15	# r15 = 0x6cb72331f5dee6a2
xor r10	# r10 = secret_key ^ code_key ^ fib_key = final_key = 0x7fa330212f68191e

push 0
pop r9

# xor the whole input with r10
xor_loop_begin:
push xor_loop_end
pop r14
je r14 r9 32

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
jmp r14 ip 894578
xor_loop_end:

push compare_to_flag
ldm.q ip, [sp]

fail_string:
.string "Wrong!!!\n"

_start:
# write(1, "Hi!\n", 4)
push 9
push hi_string
push 1
push 2
pop r2
pop r3
pop r4
pop r5
push 0x3fff8
push sp
pop r11
push print_prompt	# this will be later popped into ip
push 0x20000	# inp_addr
syscall sp	# sp = 9
pop r10	# r10 = code_key = 0x13141310041b4153
ldm.q sp, [r11]
spup
pop ip	# jump to read_input

hi_string:
.string "Welcome!\n"

# compare the encrypted input stored at input_addr to the encrypted flag
compare_to_flag:
#.break
push 0
pop r8
spup
pop r9

# repeat this block 4 times
push r9
push 0x20000	# inp_addr
add r10
ldm.q r11, [r10]
push r11
push 0x1193547e43042a69
xor r13
push r13
push r8
add r8
push 8
push r9
add r9

push r9
push 0x20000	# inp_addr
add r10
ldm.q r11, [r10]
push r11
push 0x0dfc45115637382d
xor r13
push r13
push r8
add r8
push 8
push r9
add r9

push r9
push 0x20000	# inp_addr
add r10
ldm.q r11, [r10]
push r11
push 0x20c703525d5b6f2d
xor r13
push r13
push r8
add r8
push 8
push r9
add r9

push r9
push 0x20000	# inp_addr
add r10
ldm.q r11, [r10]
push r11
push 0x47c55212705d216d
xor r13
push r13
push r8
add r8
push 8
push r9
add r9

# compare r8 with 0
push success
pop r14
je r14 r8 0

# fail
push 9
push fail_string
push 1
push 2
pop r2
pop r3
pop r4
pop r5
syscall r6
push end
pop ip

success:
push 9
push success_string
push 1
push 2
pop r2
pop r3
pop r4
pop r5
syscall r6

end:
push 0
push 3
pop r2
pop r3
syscall r4

