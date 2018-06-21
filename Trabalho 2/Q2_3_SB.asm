section .data
msg1 db 'Digite seu nome', 0ah
tammsg1 equ $-msg1
msg2 db 'Ola,'
tammsg2 equ $-msg2
msg3 db 'Seja bem vindo a calculadora',0ah
tammsg3 equ $-msg3
menu db 'Escolha uma opcao:',0ah,'1-SOMA',0ah,'2-SUB',0ah,'3-MULT'
	db 0ah,'4-DIV', 0ah,'5-MOD',0ah,'6-SAIR',0ah
tammenu equ $-menu
resultado db 0ah,'resultado :',0ah
tamresult equ $-resultado
soma db 'som'
subt db 'sub'
mult db 'mul'
divi db 'div'
modo db 'mod'

section .bss
nome resb 16
arg1 resb 12
esc resb 2
ent resb 1

section .text
global _start
_start:	mov ecx,msg1
		mov edx,tammsg1
		call output 						;printa a msg 1 na tela
		mov ecx,nome
		mov edx,16
		call input 							;recebe input de no max 16 bytes
		mov ecx,msg2
		mov edx,tammsg2
		call output 						;printa msg2 na tela
		mov ecx,nome
		mov edx,16
		call output 						;printa nome na tela
		mov ecx,msg3
		mov edx,tammsg3
		call output 						;printa msg3 na tela
pmenu:	mov ecx,menu
		mov edx,tammenu
		call output 						;printa menu na tela
		mov ecx,esc
		mov edx,2
		call input 							;recebe como input opção da calculadora
		cmp byte [esc],31h
		je Soma 							;se foi escolhido soma
		cmp byte [esc],32h
		je Sub 								;se foi escolhido subtração
		cmp byte [esc],33h
		je Mult 							;se foi escolhido multiplicação
		cmp byte [esc],34h
		je Div 								;se foi escolhido divisao
		cmp byte [esc],35h
		je Mod 								;se foi escolhido mod
		cmp byte [esc],36h
		je Sair 							;se foi escolhido sair
		jmp pmenu
Soma:	mov ecx,arg1
		mov edx,12
		call argum							;função para recuperar argumento 1
		push eax							;retorna argumento 1 em eax
		mov ecx,arg1
		mov edx,12
		call argum 							;função para receber segundo argumento
		pop ebx								;retira o argumento 1 q tava na pilha para ebx
		add eax,ebx
result:	mov ecx,resultado
		mov edx,tamresult
		call output
wat:	mov ecx,ent
		mov edx,1
		call input
		cmp byte [ent],0ah
		jne wat
		jmp pmenu
Sub:	mov ecx,arg1
		mov edx,12
		call argum							;função para recuperar argumento 1
		push eax							;retorna argumento 1 em eax
		mov ecx,arg1
		mov edx,12
		call argum 							;função para receber segundo argumento
		mov ebx,eax							;move o segundo argumento recebido para ebx
		pop eax								;retira o argumento 1 q tava na pilha para eax
		sub eax,ebx
		jmp result
Mult:	mov ecx,mult
		mov edx,3
		call output
		jmp result
Div:	mov ecx,divi
		mov edx,3
		call output
		jmp result
Mod:	mov ecx,modo
		mov edx,3
		call output
		jmp result
Sair:	mov eax,1
		mov ebx,0
		int 80h
output:	mov eax,4
		mov ebx,1
		int 80h
		ret
input:	mov eax,3
		mov ebx,0
		int 80h
		ret
argum:	mov esi,0
		mov eax,3
		mov ebx,0
		int 80h
		mov eax,0
		mov ebx,10
loop:	cmp byte [arg1+esi],0ah
		je fim1
		cmp byte [arg1+esi],'-'
		je aum
		mul ebx
		mov ecx,0
		mov byte cl,[arg1+esi]
		sub byte cl,30h
		add eax,ecx
aum:	inc esi
		cmp esi,edx
		je fim1
		jmp loop
fim1:	cmp byte [arg1],'-'
		jne fim
		mov ebx,0
		sub ebx,eax
		mov eax,ebx
fim:	ret