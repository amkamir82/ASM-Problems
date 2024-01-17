.intel_syntax noprefix
.text
.globl test_printf

test_printf:
    push rbx
    sub rsp, rdx # rsp - stack_size
    xor rax, rax # zero rax
create_stack:
    # Check end of loop
    cmp rax, rdx
    je create_stack_done
    # Move data in stack
    mov r8b, BYTE PTR [rsi + rax]
    mov BYTE PTR [rsp + rax], r8b
    # Increment the loop counter
    inc rax
    jmp create_stack
create_stack_done:
    mov rbx, rdx # rbx must be saved by printf
    call your_printf
    add rsp, rbx
    pop rbx
    ret
