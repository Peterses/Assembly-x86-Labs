SYSEXIT = 1
EXIT_SUCCESS = 0
SYSCALL = 0x80
SYSWRITE = 4
STDOUT = 1

dlugosc = 4
dlugosc_bajty = dlugosc * 8

.global main

.data

liczba1: 
.long 0x10304008, 0x701100FF, 0x45100020, 0x08570030

liczba2: 
.long 0xF040500C, 0x00220026, 0x321000CB, 0x04520031

wynik:
.long 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 

przen_wynik: 
.space 1

.text
main:

movl $0, %ebx

petla_zewn:

movl $0, %ecx
movl $0, %esi
movb $0, przen_wynik

clc
pushf

petla_wewn:

movl liczba2(, %ebx, 4), %eax
mull liczba1(, %esi, 4)

popf
adcl %ecx, %eax
pushf

mov %ebx, %edi
add %esi, %edi # w edi mamy wyliczona pozycje wyniku

cmpb $1, przen_wynik
je ustaw_flage
clc
jmp dodaj_do_wyniku

ustaw_flage:
stc

dodaj_do_wyniku:
adcl %eax, wynik(, %edi, 4)

movb $0, przen_wynik
jnc kolejne
movb $1, przen_wynik

kolejne:
movl %edx, %ecx
inc %esi
cmp $dlugosc, %esi
jl petla_wewn

inc %edi

popf
adc $0, %ecx

cmpb $1, przen_wynik
je ustaw_flage2
clc
jmp dodaj_na_koniec

ustaw_flage2:
stc

dodaj_na_koniec:
adcl %ecx, wynik(, %edi, 4)

inc %ebx
cmp $dlugosc, %ebx
jl petla_zewn

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $wynik, %ecx
mov $dlugosc_bajty, %edx
int $SYSCALL

koniec:
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $SYSCALL
