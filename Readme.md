# Primeiro Trabalho de Software Básico 
## Professor Bruno Macchiavello UnB 1/2018

Implementação em C/C++ de um método de tradução de uma linguagem de montagem simples para uma representação de código objeto.

### Compilacao
Um makefile foi disponibilizado na pasta com as seguintes opcoes:
  - **Clean:** limpa a compilacao anterior
  - **Build:** compila e liga os modulos, gerando um executavel na pasta bin
  - **Run:** executa o binario passando flags pre-especificadas

Caso o comando 'make' seja chamado sem parametro, rodamos os tres comandos acima, em ordem.

Para compilar e rodar o programa basta usar make da seguinte forma:

```
make OP=(modo) IF=(arquivo de entrada) OF=(arquivo de saida)
``` 

Desta forma, se quisessemos compilar e rodar o programa usando o parâmetro de entrada "*-p*", o arquivo de entrada "*bin.asm*" e querendo gerar o arquivo de saida "*resultado.pre*" entrariamos com 

```
make OP=p IF=bin OF=resultado
```

### Flags

Utilizamos as seguintes versoes do gcc:
 - gcc 5.4 - gcc (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0
 - gcc 7.2 - gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0

Com as seguintes flags: -std=c++11

Tomás Rosemberg

Thales Grilo
