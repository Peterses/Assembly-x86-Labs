.global dzielenie_sse
#dasdas
.text
dzielenie_sse:
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

cvtdq2ps %xmm0, %xmm2
cvtdq2ps %xmm1, %xmm3

divps %xmm2, %xmm3

movups %xmm3, (%edx, %ecx, 4)

add $4, %ecx

cmp %eax, %ecx
jl petla

pop %esi
pop %edi
pop %ebp
ret

