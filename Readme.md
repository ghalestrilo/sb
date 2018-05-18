# Primeiro Trabalho de Software Básico 
## Professor Bruno Macchiavello UnB 1/2018

Implementação em C/C++ de um método de tradução de uma linguagem de montagem simples para uma representação de código objeto.

### Compilacao
Um makefile foi disponibilizado na pasta com as seguintes opcoes:
  - **Clean:** limpa a compilacao anterior
  - **Build:** compila e liga os modulos, gerando um executavel na pasta bin
  - **Run:** executa o binario passando flags pre-especificadas

Caso o comando 'make' seja chamado sem parametro, rodamos os tres comandos acima, em ordem.

### Flags

Utilizamos as seguintes versoes do gcc:
 - gcc 5.4 - gcc (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0
 - gcc 7.2 - gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0

Com as seguintes flags: -std=c++11

Tomás Rosemberg

Thales Grilo


### TODO

- Preprocessador:
  - Expandir macros (levando parametros em consideracao)
  - Resolver IF/EQUs
  - Remover comentarios

- Parser:
  - Ignorar quebras de linhas
    - Levar em consideracao o numero de parametros que o comando exige
    - Continuar recebendo parametros ate o numero ter sido alcancado
    - Caso algum parametro seja palavra reservada, isso e um erro sintatico, pois com certeza era comando de outra linha
  - Ler Opcode (no caso de comandos) e botar no valor de value (expressao)
  - Ler Valor (no caso de diretiva CONST) e botar no valor de value (expressao) - 0 no caso de SPACE.

- Lexer:
  - Tokens tem que virar uma struct para levar em consideracao a linha e posicao encontradas no arquivo original - podemos usar isso para printar erros em tela.

- @ghalestrilo:
  - Migrar `token` -> `tokenstruct`, deletando token original no processo
  - Utilizando novo tipo de token, resolver parser::parseline, para interpretar diretivas utilizando `res.exp.token.position` para comparacoes posicionais na linha (tipo section vir no comeco da linha etc). O processo envolve:
    - Ignorar posicionalmente token section, caso corretamente formatada.
    - Const determinar o valor imediato da expressao, sendo tambem ignorada posicionalmente
    - Space como acima, porem seta valor para 0.
  - Fazer parser ignorar tokens vazias ("") para remover os '0's do assembler