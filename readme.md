## Parte 1:

@ghalestrilo (28/06/2018):
Em reuniao com o professor Bruno, os seguintes erros foram apontados para o Trabalho I:

**Relevantes** - Erros que vao afetar o trabalho II, e devem ser corrigidos
- Montador:
 - Incapacidade de processar vetores
  - Declaracao: VEC: SPACE X
  - Acesso: ADD VEC, VEC+1
 - Valores Numericos Hexadecimais, e valores negativos (CONST da muito erro com isso, nao deixa haverem contantes negativas)
  - 0xdeadbeef
  - 0x01234567
  - -0xf000baaa
  - -12
- Pre-processador:
 - Macros: Parametros nao substituidos (substituidos pelo proprio nome, nao pelo valor), tipo &A -> A
 -

**Passados** - Erros cuja solucao nao afetaria o trabalho II, e devem ser ignorados
- Deteccao de Erros:
 - Modificacao de valores CONST
 - Label nao declarado em SECTION DATA
 - Desvio de secao (Jumps de TEXT para DATA)
 - Desvio para rotulos nao declarados
 - Space com mais de um argumento
 - Space negativo
 - Instrucoes em DATA
 - Diretivas de Dados em TEXT
 - Divisao por 0
 - Macro sem Endmacro (*preprocessador*)
 - Hexadecimal Mal-formatado (sem 0x, ou com digitos maiores que 'f')
 - INPUT sem argumentos
