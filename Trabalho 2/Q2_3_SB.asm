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
arg2 resb 12
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
		jmp pmenu							;se nada foi escolhido, printa o menu novamente

Soma:	mov ecx,arg1						;coloca argumento em ecx
		mov edx,12							;coloca o tamanho do argumento em edx
		call argum							;função para recuperar argumento 1,retorna o valor de arguemento em eax
		push eax							;salva o valor de argumento 1 na pilha
		mov ecx,arg1						;coloca argumento em ecx
		mov edx,12							;coloca tamanho do argumento em edx
		call argum 							;função para receber segundo argumento
		pop ebx								;retira o argumento 1 q tava na pilha para ebx
		add eax,ebx							;adiciona argumento 2 e argumento 1
		mov ecx,resultado					;responsavel por printar na tela a mensagem de resultado
		mov edx,tamresult
		push eax
		call output
		pop eax
		call wnum
		jmp wat

wat:	mov ecx,ent							;procedimento para, apos o resultado, esperar o input de um enter para voltar ao menu
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
		mov ecx,resultado					;responsavel por printar na tela a mensagem de resultado
		mov edx,tamresult
		call output
		jmp wat

Mult:	mov ecx,arg1
		mov edx,12
		call argum							;função para recuperar argumento 1
		push eax							;retorna argumento 1 em eax
		mov ecx,arg1
		mov edx,12
		call argum 							;função para receber segundo argumento
		mov ebx,eax							;move o segundo argumento recebido para ebx
		pop eax								;retira o argumento 1 q tava na pilha para eax
		imul ebx
		mov ecx,resultado					;responsavel por printar na tela a mensagem de resultado
		mov edx,tamresult
		call output
		jmp wat

Div:	mov ecx,arg1
		mov edx,12
		call argum							;função para recuperar argumento 1
		push eax							;retorna argumento 1 em eax
		mov ecx,arg1
		mov edx,12
		call argum 							;função para receber segundo argumento
		mov ebx,eax							;move o segundo argumento recebido para ebx
		pop eax								;retira o argumento 1 q tava na pilha para eax
		mov edx,0
		cmp eax,0
		jb posit
		mov edx,-1
posit:	idiv ebx
		mov ecx,resultado					;responsavel por printar na tela a mensagem de resultado
		mov edx,tamresult
		call output
		jmp wat

Mod:	mov ecx,arg1
		mov edx,12
		call argum							;função para recuperar argumento 1
		push eax							;retorna argumento 1 em eax
		mov ecx,arg1
		mov edx,12
		call argum 							;função para receber segundo argumento
		mov ebx,eax							;move o segundo argumento recebido para ebx
		pop eax								;retira o argumento 1 q tava na pilha para eax
		mov edx,0
		cmp eax,0
		jb pos
		mov edx,-1
pos:	idiv ebx
		mov ecx,resultado					;responsavel por printar na tela a mensagem de resultado
		mov edx,tamresult
		call output
		jmp wat


Sair:	mov eax,1							;Procedimento responsavel pelo fim da execução do programa
		mov ebx,0
		int 80h

output:	mov eax,4							;função responsavel por printar na tela uma string,
		mov ebx,1							;apos receber os parametros pro registrador ecx e edx
		int 80h
		ret

input:	mov eax,3							;função responsavel por receber do usuario um string
		mov ebx,0							;recebe os parametros pelos registradores ecx e edx
		int 80h
		ret

;Função argum começa na label argum e termina na label fim, é responsavel por receber,via input, o argumento no formato string e
;converte-lo para o seu valor numerico equivalente e armazenar esse valor no registrador eax
argum:	mov esi,0							;começa zerando esi
		mov eax,3							;recebe via input
		mov ebx,0
		int 80h
		mov eax,0							;zera eax
		mov ebx,10							;move 10 para o ebx
loop:	cmp byte [arg1+esi],0ah				;checa se o bite é um enter
		je fim1								;se for enter pula para o fim
		cmp byte [arg1+esi],'-'				;checa se o byte é um sinal de menos
		je aum 								;se for, pula para a checagem do proximo byte
		mul ebx								;multiplica o atual valor de eax por 10
		mov ecx,0							;zera ecx
		mov byte cl,[arg1+esi]				;move o byte na posição para cl (ecx low)
		sub byte cl,30h						;tira o valor em ascii para o numero em ascci virar numero de verdade
		add eax,ecx 						;adiciona o valor encontrado em eax
aum:	inc esi 							;incremente meu contador de loop (esi)
		cmp esi,edx 						;checa se o contador de loop ja é do tamanho do argumento
		je fim1								;se for vai para o fim
		jmp loop							;se nao for, vai volta pro processamento do proximo byte
fim1:	cmp byte [arg1],'-'					;checa se o primeiro byte é um sinal de menos
		jne fim 							;se nao for, vai pro fim, se for negativa o valor de eax
		mov ebx,0							;zera ebx
		sub ebx,eax							;subtrai 0 por eax e move o resultado para eax
		mov eax,ebx
fim:	ret

wnum:	mov esi,0
		mov ecx,10
lp:		cmp eax,0
		je end
		mov edx,0
		idiv ecx
		add byte edx,30h
		mov byte [arg2+esi],dl
		inc esi
		jmp lp
end:	mov eax,4
		mov ebx,1
		mov ecx,arg2
		mov edx,esi
		int 80h
		ret