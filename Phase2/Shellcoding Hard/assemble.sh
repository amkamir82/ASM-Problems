#!/bin/bash
gcc -nostdlib -static -o elf-shellcode $1
objcopy --dump-section .text=raw-shellcode elf-shellcode
