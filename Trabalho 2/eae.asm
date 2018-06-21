section .data
response db 'y'
tablel times 20 dw 1
noome db 'Jim Ray'
section .text
global _start
_start:	
aa		mov al, [response]
bb		mov dx, [tablel]
cc		mov word [response], 'N'
ddd		mov al, [response]
vqv		mov eax,1
		mov ebx,0
		int 80h