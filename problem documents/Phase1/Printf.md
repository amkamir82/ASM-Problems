یک subroutine بنویسید که یک نسخه‌ی ساده شده‌ی تابع printf باشد. به این تابع در ابتدا آدرس رشته‌ی format string در رجیستر RDI باید پاس داده شود. سپس بقیه‌ی آرگومان‌های تابع باید در استک طوری به تابع پاس داده شوند که اولین آرگومان در پایین ترین آدرس استک، بالای return address قرار داشته باشد.
تابع شما باید از سه نوع format specifier پشتیبانی بکند:
%s: برای چاپ یک رشته null terminated به کار می‌رود.
%u: یک عدد 64 بیتی unsigned را چاپ می‌کند.
%d: یک عدد 64 بیتی signed را چاپ می‌کند.
در این سوال تضمین می‌شود که همیشه تمامی format specifierهای داخل رشته valid و از چهار نوع بالا باشند. برای درک بهتر به یکی از نوع‌های صدا کردن این تابع توجه کنید:
```asm
print_stuff:
    sub rsp, 1
    push OFFSET RANDOM_STRING
    mov rax, -10
    push rax
    mov rax, 10
    push rax
    mov rdi, OFFSET FORMAT_STRING
    call your_printf


.data
FORMAT_STRING: .string "My number: %d %u. Also look at this: %s\n"
RANDOM_STRING: .string "Random string!"
```