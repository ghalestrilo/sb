.PHONY: hello
hello:
	nasm -f elf -o hello.o hello.asm
	ld -m elf_i386 -o hello hello.o
	./hello

deb:
	gdb Q2_3_SB

gdb: deb
