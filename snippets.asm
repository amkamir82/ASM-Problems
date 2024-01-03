; https://alexaltea.github.io/blog/posts/2016-10-12-xchg-rax-rax-solutions/
.text:
    ; 0
    not      rbx
    inc      rbx
    neg      rbx
    ; 1
    add      rax,rcx
    rcr      rax,1
    ; 2
    mov      rsi,rdi
    and      rsi,rdx
    xor      rdi,rdx
    shr      rdi,1
    add      rdi,rsi
    
    ; 3
    db c2  'a'

    mov al, c2
    and al, 5Fh
    mov c2, al
    
    ; 4
    mov      rbx,rax
    not      rbx
    mov      rdx,0x8080808080808080
    and      rbx,rdx
    mov      rdx,0x0101010101010101
    sub      rax,rdx
    and      rax,rbx