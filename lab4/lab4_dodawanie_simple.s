
.global dodawanie_sisd

.text

dodawanie_sisd:
push %ebp
mov %esp, %ebp

push %edi
push %esi
push %ebx

mov 8(%ebp), %edi
mov 12(%ebp), %esi
mov 16(%ebp), %edx
mov 20(%ebp), %eax

mov $0, %ecx

petla2:
mov (%edi, %ecx, 4), %ebx
add (%esi, %ecx, 4), %ebx
mov %ebx, (%edx, %ecx, 4)

add $1, %ecx

cmp %eax, %ecx
jl petla2

pop %ebx
pop %esi
pop %edi
pop %ebp
ret
