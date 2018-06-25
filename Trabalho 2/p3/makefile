.PHONY: run
run:
	nasm -f elf -o Q2_3_SB.o Q2_3_SB.asm
	ld -m elf_i386 -o Q2_3_SB Q2_3_SB.o
	./Q2_3_SB
deb:
	gdb Q2_3_SB

gdb: deb

