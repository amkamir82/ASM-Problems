# خود تغییر

تکه کد اسمبلی زیر را تحلیل کنید و بگویید چه کاری می کند. توضیح دهید دقیقا هر دستور با چه هدفی در کد قرار گرفته است و مقدار بازگشتی خروجی کد چیست؟

```
func:
          add rax, rax
          ret     
_start:  
          call func
          mov rcx, 7
          loop1:
              add qword [func], 0x80000
              call func
              loop loop1
          
          or qword [func], 0x04
          call func


          mov rcx, 7
          loop2:
              sub qword [func], 0x80000
              call func
              loop loop2           


          mov      rdi, rax
          mov      rax, 60                 
          syscall 
```
