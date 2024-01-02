; ----------------------------------------------------------------------------------------
; Writes "Hello, World" to the console using only system calls. Runs on 64-bit Linux only.
; To assemble and run:
;
;     nasm -felf64 hello.asm && ld hello.o && ./a.out
; ----------------------------------------------------------------------------------------

            global    _start

            section   .text


func:
            add rax, rax
            ret       
_start:   

            mov rdi, func
            mov rsi, func
            and rsi, 4095
            sub rdi, rsi
            mov rsi, 4096
            mov rdx, 7

            mov rax, 10
            syscall ; mprotect

            mov rbx, 1
            mov rcx, 1
            mov rdx, 1 
            mov rax, 0
            call func

            mov rcx, 7
            mov r9, 1
            shl r9, 19
            ; first for
            loop1:
                mov r10, [func] ; instruction
                ; modify code
                add r10, r9
                mov [func], r10
                call func
                loop loop1
            
            ; change instruction for r8 to r15
            mov r9, 4
            mov r10, [func]
            or r10, r9
            mov [func], r10

            call func

            ; here we go again
            mov rcx, 7
            mov r9, 1
            shl r9, 19

            loop2:
                mov r10, [func] ; instruction
                ; modify code
                sub r10, r9
                mov [func], r10
                call func
                loop loop2            




            mov       rdi, rax
            mov       rax, 60                 ; system call for exit
            syscall                           ; invoke operating system to exit