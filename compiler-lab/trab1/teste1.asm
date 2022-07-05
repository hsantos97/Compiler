extern printf
extern scanf
section .data
fmt_d: db "%ld", 0
fmt_f: db "%f", 0
fmt_s: db "%s", 0
fmt_dln: db "%ld", 10, 0
fmt_fln: db "%f", 10, 0
fmt_sln: db "%s", 10, 0

x: dq 0
y: dq 0
total: dq 0
media: dq 0
impar: dq 0

section .text
global main

main:
mov rdi,fmt_f
mov rsi,x
mov rax,0
call scanf
mov rdi,fmt_f
mov rsi,y
mov rax,0
call scanf
mov rbx,[x]
push rbx
mov rbx,[y]
push rbx
pop rcx
pop rbx
add rbx,rcx
push rbx
pop rbx
mov [total],rbx
mov rbx,[total]
push rbx
mov rbx,2
push rbx
pop r8
pop rax
xor rdx,rdx
idiv r8
push rax
pop rbx
mov [media],rbx
mov rdi,fmt_f
mov rsi,[media]
mov rax,0
call printf
mov rbx,0
push rbx
pop rbx
mov [impar],rbx
label2:
mov rbx,0
push rbx
pop rcx
mov rbx, [total]
cmp rbx, rcx
jng label3
mov rbx,0
push rbx
pop rcx
mov rbx, [impar]
cmp rbx, rcx
jne label0
mov rbx,1
push rbx
pop rbx
mov [impar],rbx
jmp label1
label0:
mov rbx,0
push rbx
pop rbx
mov [impar],rbx
label1:
mov rbx,[total]
push rbx
mov rbx,1
push rbx
pop rcx
pop rbx
sub rbx,rcx
push rbx
pop rbx
mov [total],rbx
jmp label2
label3:
mov rdi,fmt_d
mov rsi,[impar]
mov rax,0
call printf
mov rax,0
ret
