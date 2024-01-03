#!/bin/sh
gcc -fno-pie -no-pie -g -o printf main.c sample_printf.S run_printf.S