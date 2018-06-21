section .data
msg db 'BOCADEPELO' ,0dh, 0ah
tam equ $-msg
section .text
global _start
_start:	mov eax,4
		mov ebx,1
		mov ecx,msg
		mov edx,tam
		int 80h
		mov ebx,msg
		mov eax,tam
		push eax
		push ebx
mais:	pop ebx
		pop eax
		add byte [ebx],32
		mov byte cl,[ebx]
		mov dl,cl
oi:		add ebx,1
		dec eax
		push eax
		push ebx
		mov eax,4
		mov ebx,1
		mov ecx,msg
		mov edx,tam
		int 80h
		jnz mais
		mov eax,1
		mov ebx,0
		int 80h