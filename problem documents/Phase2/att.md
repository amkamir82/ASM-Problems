# اتت

تکه کد اسمبلی زیر به سینتکس AT&T نوشته شده است. آن را تحلیل کنید و بگویید که چه کار می‌کند؟

```
my_function:
   movq    8(%rsp), %rax
   fldl    8(%rsp)
   movabsq $6910469410427058089, %rdx
   fmuls   .LC0(%rip)
   shrq    %rax
   subq    %rax, %rdx
   movq    %rdx, -8(%rsp)
   fmull   -8(%rsp)
   fmull   -8(%rsp)
   fsubrs  .LC1(%rip)
   fmull   -8(%rsp)
   fstpl   (%rdi)
   ret
.LC0:
   .long   1056964608
.LC1:
   .long   1069547520
```
