run:
	nasm -f elf -o Q2_3_SB.o Q2_3_SB.asm
	ld -m elf_i386 -o Q2_3_SB Q2_3_SB.o
	./Q2_3_SB

.PHONY: hello
hello:
	nasm -f elf -o hello.o hello.asm
	ld -m elf_i386 -o hello hello.o
	./hello

eae:
	nasm -f elf -o eae.o eae.asm
	ld -m elf_i386 -o eae eae.o
	./eae

deb:
	gdb Q2_3_SB