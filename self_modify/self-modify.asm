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


            call func

            mov rcx, 7
            ; first for
            loop1:
                ; modify code
                add qword [func], 0x80000
                call func
                loop loop1
            
            ; change instruction for r8 to r15
            or qword [func], 0x04
            call func


            ; here we go again
            mov rcx, 7
            loop2:
                ; modify code
                sub qword [func], 0x80000
                call func
                loop loop2            

            mov       rdi, rax
            mov       rax, 60                 ; system call for exit
            syscall                           ; invoke operating system to exit
                       
