import sys
import os
import subprocess as sp

if len(sys.argv) < 2:
	exit(2)

with open("AA", "rb") as flag_file:
	flag = flag_file.read().strip()
	flag = bytes(filter(lambda x: ord("A") <= x <= ord("Z"), flag))
print(flag)

tmpdir = sp.check_output("mktemp -d", shell=True).strip().decode()
print(tmpdir)

elf_shellcode = os.path.join(tmpdir, "elf-shellcode")
raw_shellcode = os.path.join(tmpdir, "raw-shellcode")
#os.system("gcc -nostdlib -static -o %s '%s'" % (elf_shellcode, sys.argv[1]))
#os.system("objcopy --dump-section .text=%s %s" % (raw_shellcode, elf_shellcode))
os.system("nasm '%s' -o '%s'" % (sys.argv[1], raw_shellcode))

with open(raw_shellcode, "rb") as f:
	shellcode = f.read()

if len(shellcode) > 128:
	print("bad length")
	exit(1)

p = sp.Popen(["./driver"], stdin=sp.PIPE, stdout=sp.PIPE, stderr=sp.PIPE)
out, err = p.communicate(input=shellcode)
if len(err) > 0 or out.strip() != flag:
	print("bad output")
	print(out)
	print(err)
	exit(1)

print("correct")
exit(0)
