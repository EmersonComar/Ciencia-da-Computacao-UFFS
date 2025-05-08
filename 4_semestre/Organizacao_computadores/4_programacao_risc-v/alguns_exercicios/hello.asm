.data
	hello: .asciz "Hello World"

.text
.globl main

main:
	li a7, 4
	la a0, hello
	ecall
	
	li a7, 10
	ecall