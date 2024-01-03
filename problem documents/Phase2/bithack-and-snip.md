# اسنیپ-هاک

تکه کدهای زیر را تحلیل کنید و توضیح دهید هر کدام چه کاری انجام میدهد (چه مقداری را محاسبه میکند و کجا ذخیره میکند؟) 

```
   ; 0
  not     rbx
  inc     rbx
  neg     rbx

   ; 1
  add     rax,rcx
  rcr     rax,1

   ; 2
  mov     rsi,rdi
  and     rsi,rdx
  xor     rdi,rdx
  shr     rdi,1
  add     rdi,rsi
  
   ; 3
.data
   c2 byte 'a'


.text
  mov al, c2
  and al, 5Fh
  mov c2, al
  
   ; 4
  mov     rbx,rax
  not     rbx
  mov     rdx,0x8080808080808080
  and     rbx,rdx
  mov     rdx,0x0101010101010101
  sub     rax,rdx
  and     rax,rbx
```
