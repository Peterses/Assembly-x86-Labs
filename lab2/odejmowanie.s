SYSEXIT = 1
EXIT_SUCCESS = 0
SYSCALL = 0x80
SYSWRITE = 4
STDOUT = 1

dlugosc = 4
dlugosc_bajty = dlugosc * 4

.global main

.data
liczba1: 
.long 0x10304008, 0x701100FF, 0x45100020, 0x08570030

liczba2: 
.long 0xF040500C, 0x00220026, 0x321000CB, 0x04520031


przeniesienie:
.byte 1

.text
main:
mov $0, %esi
clc
pushf

petla:
popf
mov liczba2(, %esi, 4), %eax
sbb %eax, liczba1(, %esi, 4)
inc %esi
pushf
cmp $dlugosc, %esi
jl petla

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $liczba1, %ecx
mov $dlugosc_bajty, %edx
int $SYSCALL


koniec:
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $SYSCALL
