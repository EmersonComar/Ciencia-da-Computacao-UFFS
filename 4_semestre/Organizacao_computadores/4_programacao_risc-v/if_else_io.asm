        .data
x:      .space  4
y:      .word   4
a:      .word   4
e_x:    .string "Entre x: "
e_y:    .string "Entre y: "
m_x:    .string "x eh maior\n"
m_nx:   .asciz  "x nao eh maior\n"


	.text
main: 
	la 	  a0, e_x      # imprime mensagem X
	li 	  a7, 4
	ecall

	addi  	  a7, zero, 5  #lê inteiro
	ecall	
        mv        s0, a0     #atribui X a s0

	la 	  a0, e_y    # imprime mensagem Y
	li 	  a7, 4
	ecall
        
	li 	  a7, 5        #lê inteiro
	ecall	
        add       s1, zero, a0 #atribui Y a s1


logica:
    	bgt      s0, s1, corpo_if
corpo_else:
    	la 	 a0, m_nx    # imprime Y maior
	li       a7, 4
	ecall
    	li       s2, -1
    	la       t0, a
    	sw       s2, 0 (t0) # atribui valor de 'a'
    	j        fim
corpo_if:
    	la 	 a0, m_x    # imprime X maior
	li       a7, 4
	ecall
    	li       s2, 1
    	la       t0, a
    	sw       s2, 0 (t0) # atribui valor de 'a'
fim:
    	li       a7, 10
	ecall    
