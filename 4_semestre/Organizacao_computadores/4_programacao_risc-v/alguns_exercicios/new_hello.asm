.data
	hello: .asciz "Hello, RISC-V!\n"
	name: .asciz "Emerson\n"
	
.text
.globl main

main:
	li a7, 4
	la a0, hello
	ecall
	
	la a0, name
	ecall
	
	li a7, 10
	ecall