.data

msg:
	.ascii "Hello, world!\n"
	len = . - msg

.text
	.global main

main:
	movq $1, %rax
	movq $1, %rdl
	movq $msq, %rsi
	movq $len, %rdx
	syscall

	movq $60, %rax
	xorq %rdi, %rdi
	syscall
