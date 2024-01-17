import sys
import struct
import re

p64 = lambda x: struct.pack("<Q", x)

label_refs = {}
code = b""

class Translator:
	@staticmethod
	def push(op, operand):
		if get_register(operand) != None:
			return bytes([get_register(operand)])
		try:
			return b"\x30" + p64(int(operand, 16))
		except ValueError:
			label_refs[len(code) + 1] = operand
			return b"\x30" + p64(0)
	
	@staticmethod
	def pop(op, reg):
		return bytes([0x10 | get_register(reg)])
	
	@staticmethod
	def syscall(op, reg):
		return bytes([0x20 | get_register(reg)])
	
	@staticmethod
	def arithmetic(op, reg):
		return bytes([0x40 + ("add", "sub", "xor").index(op)]) + \
			bytes([get_register(reg)])
	
	@staticmethod
	def mem(op, dst, src):
		return bytes([0x50 + ("stm.b", "stm.q", "ldm.b", "ldm.q").index(op)]) + \
			bytes([(get_register(dst) << 4) | get_register(src)])
	
	@staticmethod
	def jump(op, addr_reg, cond_reg, imm):
		global code, label_refs
		return bytes([0x60 + ("jmp", "je").index(op)]) + \
			bytes([(get_register(addr_reg) << 4) | get_register(cond_reg)]) + p64(int(imm))
	
	@staticmethod
	def string_literal(op, *parts):
		# return " ".join(map(lambda x: x.replace('"', "").replace("\\n", "\n"), parts)).encode()
		return parts[0].strip('"').replace("\\n", "\n").encode()
	
	@staticmethod
	def sp_up(op):
		return b"\x70"
	
	@staticmethod
	def breakpoint(op):
		return b"\x62"

Translator.functions_map = {
	"push": Translator.push,
	"pop": Translator.pop,
	"syscall": Translator.syscall,
	"add": Translator.arithmetic,
	"sub": Translator.arithmetic,
	"xor": Translator.arithmetic,
	"ldm.b": Translator.mem,
	"stm.b": Translator.mem,
	"ldm.q": Translator.mem,
	"stm.q": Translator.mem,
	"jmp": Translator.jump,
	"je": Translator.jump,
	"spup": Translator.sp_up,
	".string": Translator.string_literal,
	".break": Translator.breakpoint
}

def get_register(name):
	if name == "ip":
		return 0
	elif name == "sp":
		return 1
	elif re.fullmatch(r"r\d+", name):
		return int(name[1:])
	else:
		return None

def translate_instruction(line):
	line = line.replace(",", "").replace("[", "").replace("]", "").split()
	return Translator.functions_map[line[0]](*line)

def assemble(asm):
	global code, label_refs

	# detect labels
	labels = {}
	for i in range(len(asm)):
		if (asm[i][-1] == ":"):
			labels[asm[i][:-1]] = -1

	# assemble instructions
	for i in range(len(asm)):
		print(hex(len(code)) + ": " + asm[i])
		if (asm[i][-1] != ":"):
			code += translate_instruction(asm[i])
		else:
			labels[asm[i][:-1]] = len(code)

	# fill label addresses
	code = list(code)
	for offset in label_refs:
		target = labels[label_refs[offset]]
		code[offset:offset + 8] = list(p64(target))
	code = bytes(code)

	return code

def clean_code(asm):
	res = []
	for line in asm:
		if ("#" in line):
			line = line[:line.index("#")]
		line = line.strip()
		if line != "":
			res.append(line)
	return res

def main():
	if len(sys.argv) < 2:
		print("Usage: %s <filename>" % sys.argv[0])
		exit(1)
	with open(sys.argv[1]) as f:
		asm_code = f.read().strip().splitlines()
	code = assemble(clean_code(asm_code))
	step = 24
	for i in range(0, len(code), step):
		print('"' + "".join(map(lambda x: "\\x%02x" % x, list(code[i:i + step]))) + '"')

if __name__ == "__main__":
	main()
