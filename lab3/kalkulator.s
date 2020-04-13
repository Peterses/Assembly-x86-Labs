SYSEXIT = 1
EXIT_SUCCESS = 0
SYSCALL = 0x80

.data
liczba1:
.float 4.5

liczba2:
.float 5.7

liczba3:
.float -4.8

double_prec:
.word 0x27F 

single_prec:
.word 0x7F 

round_down:
.word 0x77F

round_up:
.word 0xB7F

round_zero:
.word 0xF7F

.global main

.text
main:

jmp add1

down_round:
fldcw round_down

jmp wybor

up_round:
fldcw round_up

jmp wybor

zero_round:
fldcw round_zero

jmp wybor

prec_single:
fldcw single_prec

jmp wybor

prec_double:
fldcw double_prec

wybor:

jmp koniec

add1:
flds liczba1
fadds liczba2

jmp koniec

sub2:
flds liczba3
fsubs liczba2

jmp koniec

div3:
flds liczba1
flds liczba2
fdivp %st(0), %st(1)

jmp koniec

wyjatki:
fldz
fmuls liczba2

flds liczba2
fdiv %st(1), %st(0) # +inf

fldz
fmuls liczba3 # -0

flds liczba2
fdiv %st(1), %st(0) # -inf

flds liczba3
fsqrt


koniec:
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $SYSCALL
