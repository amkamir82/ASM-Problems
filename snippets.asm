; https://alexaltea.github.io/blog/posts/2016-10-12-xchg-rax-rax-solutions/
.text:
    ; 0
    not      rax
    inc      rax
    neg      rax
    ; 1
    add      rax,rdx
    rcr      rax,1
    ; 2
    mov      rcx,rax
    and      rcx,rdx

    xor      rax,rdx
    shr      rax,1

    add      rax,rcx

    ; 3
    mov      rdx,rax
    not      rdx
    mov      rcx,0x8080808080808080
    and      rdx,rcx
    mov      rcx,0x0101010101010101
    sub      rax,rcx
    and      rax,rdx

    ; 4