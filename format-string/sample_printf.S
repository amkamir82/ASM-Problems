.intel_syntax noprefix
.text
.globl your_printf

.macro stack_alignment_begin
    push rbp
    mov rbp, rsp
    mov rax, rsp
    and rax, 15
    sub rsp, rax
.endm

.macro stack_alignment_done
    mov rsp, rbp
    pop rbp
.endm

print_int:
    stack_alignment_begin

    mov rsi, rdi
    mov rdi, OFFSET print_int_format
    xor rax, rax
    call printf
    
    stack_alignment_done
    ret

print_uint:
    stack_alignment_begin

    mov rsi, rdi
    mov rdi, OFFSET print_uint_format
    xor rax, rax
    call printf
    
    stack_alignment_done
    ret

print_char:
    stack_alignment_begin

    call putchar
    
    stack_alignment_done
    ret


print_string:
    stack_alignment_begin

    mov rsi, rdi
    mov rdi, OFFSET print_string_format
    xor rax, rax
    call printf
    
    stack_alignment_done
    ret

your_printf:
    push rbp
    mov rbp, rsp
    # Print the source
    xor rcx, rcx # rax is our counter
    lea rsi, [rsp + 16] # 8 bytes of pusehd rbp and 8 bytes of return address
loop_on_format:
    # Check the null terminator
    mov r8b, BYTE PTR [rdi + rcx]
    test r8b, r8b
    jz printf_done
    # Check %
    cmp r8b, '%'
    je handle_percent
    # Just print the char and done
    push rcx
    push rdi
    push rsi
    xor rdi, rdi
    mov dil, r8b
    call print_char
    pop rsi
    pop rdi
    pop rcx
    jmp loop_on_format_done
handle_percent:
    # What format is this?
    inc rcx
    mov r8b, BYTE PTR [rdi + rcx]
    cmp r8b, 's' # print string
    je handle_print_string
    cmp r8b, 'd' # print signed int
    je handle_print_int
    cmp r8b, 'u' # print unsigned int
    je handle_print_uint
handle_print_string:
    push rcx
    push rdi
    push rsi
    mov rdi, QWORD PTR [rsi] # load from stack
    call print_string
    pop rsi
    pop rdi
    pop rcx
    add rsi, 8 # add 8 bytes to read bytes
    jmp loop_on_format_done
handle_print_int:
    push rcx
    push rdi
    push rsi
    mov rdi, QWORD PTR [rsi] # load from stack
    call print_int
    pop rsi
    pop rdi
    pop rcx
    add rsi, 8 # add 8 bytes to read bytes
    jmp loop_on_format_done
handle_print_uint:
    push rcx
    push rdi
    push rsi
    mov rdi, QWORD PTR [rsi] # load from stack
    call print_uint
    pop rsi
    pop rdi
    pop rcx
    add rsi, 8 # add 8 bytes to read bytes
    jmp loop_on_format_done
loop_on_format_done:
    inc rcx
    jmp loop_on_format
printf_done:
    mov rsp, rbp
    pop rbp
    ret

.data
print_int_format: .string    "%ld"
print_uint_format: .string   "%lu"
print_string_format: .string "%s"
