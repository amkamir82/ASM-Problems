from pwn import *
import random
import string

context.log_level = "ERROR"

def get_rand_input():
	c = random.randint(0, 1)
	if c:
		n = 32
	else:
		n = random.randint(0, 60)
	inp = "".join(random.choice(string.ascii_letters + string.digits + string.punctuation) for i in range(n))
	return inp

def run():
	p = process("./chall")
	p.recvuntil(b"Key:")
	inp = get_rand_input().encode()
	p.sendline(inp)
	out = p.recvall()
	if b"Correct" in out:
		print("inp = %s => correct" % inp)
		exit()
	elif b"Wrong" not in out:
		print("inp = %s => no output" % inp)
		exit()

for i in range(1000):
	if (i % 100 == 0):
		print(i)
	run()

