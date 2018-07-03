# Software Básico (UnB)

Repositório para concentrar os trabalhos semestrais da disciplina.
- Semestre: 01/2018
- Professor: Bruno Macchiavello

Consiste das seguintes pastas

## Trabalho 1:

## Trabalho 2:
Dividido em três partes, cada uma com sua ../p1/respectiva pasta.

- **p1:** Compilador, adaptado para acomodar a compilação de múltiplos módulos. Comandos para compilação e execução:
  - make
  - ./bin/compilador.exe -o <modulo1> <modulo2>

  O programa automaticamente infere que um arquivo de um módulo apenas é um executável standalone. Módulos e programas são compilados para arquivos homônimos, no mesmo diretório, com a extensão '.o'. Alguns arquivos fonte são disponibilizados na pasta 'res', tornando-se conveniente, então, o comando:
  **Não incluir extensão dos arquivos fonte no nome dos modulos - '.asm' é automaticamente inferido**

  - ./bin/compilador.exe -o res/<modulo1> res/<modulo2>
  
- **p2:** Ligador, capaz de ligar módulos montados a partir de p1
  - make
  - ./ligador.exe -o <modulo1> <modulo2>

  O programa automaticamente infere que um arquivo de um módulo apenas é um executável standalone. Módulos e programas são compilados para arquivos homônimos, no mesmo diretório, com a extensão '.o'.
  **Não incluir extensão dos arquivos fonte no nome dos modulos - '.o' é automaticamente inferido**

  Arquivos compilados pela parte 1 encontram-se em '../p1/res', podendo ser chamados como

  - ./ligador.exe "../p1/res/<modulo1>" "../p1/res/<modulo2>"

    

- **p3:** Exercício de Linguagem Assembly x86.
  - O comando 'make' automaticamente compila e roda o executável em sistemas ubuntu.