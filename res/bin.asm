OI: Equ 1
vqv : equ 0
m: Macro 
load A
Endmacro
N : Macro &par_1
sub &par_1
Endmacro
O : Macro &par_2,&par_3
sub &par_2
add &par_3
Endmacro
P: Macro &par_4,&par_5,&par_6
sub &par_4
add &par_5
add &par_6
Endmacro
section TEXT ;asdcasdcasdcasdc
INPUT OLD_DATA ;ASDASDASD
If oi
Esta linha mantem
if vqv
Esta linha tira
LOAD OLD_DATA
ANTES_MACRO_M
m
ANTES_MACRO_N
n num1
ANTES_MACRO_O
o num2,num3
ANTES_MACRO_P
p num4,num5,num6
COPY NEW_DATA,OLD_DATA
COPY a,b
LOAD OLD_DATA
JMPP L1
STOP
SECTION DATA
DOIS: CONST 2
OLD_DATA: SPACE
NEW_DATA: SPACE
TMP_DATA: SPACE


; L1       = 4
; DOIS     = 27
; OLD_DATA = 28
; OLD_DATA = 29
; OLD_DATA = 30