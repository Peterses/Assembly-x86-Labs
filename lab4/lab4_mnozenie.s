.global mnozenie_sse

.text
mnozenie_sse:
push %ebp
mov %esp, %ebp

push %edi
push %esi

mov 8(%ebp), %edi
mov 12(%ebp), %esi
mov 16(%ebp), %edx
mov 20(%ebp), %eax

xor %ecx, %ecx

petla:
movdqu (%edi, %ecx, 4), %xmm0
movdqu (%esi, %ecx, 4), %xmm1

pmulld %xmm0, %xmm1

movdqu %xmm1, (%edx, %ecx, 4)

add $4, %ecx

cmp %eax, %ecx
jl petla

pop %esi
pop %edi
pop %ebp
ret

