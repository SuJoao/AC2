# Ex 1 b)

        .equ ADDR_BASE_HI,0xBF88 

        .equ TRISE,0x6100 
        .equ PORTE,0x6110           
        .equ LATE,0x6120  

        .equ TRISB,0x6040                  
        .equ PORTB,0x6050                  
        .equ LATB, 0x6060                  

        .data
        .text
        .globl main

main:

        lui $t0, ADDR_BASE_HI

        lw $t1, TRISB($t0)
        ori $t1, $t1, 0x000F                    # RE3 a RE0 (SW) = 1  (input)
        sw $t1, TRISB($t0)

        lw $t1, TRISE($t0)
        andi $t1, $t1, 0xFFF0                   # RE3 a RE0 (LED) = 0 (output)  
        sw $t1, TRISE($t0)

while: 

        lw $t1, PORTB($t0)                      
        andi $t1, $t1, 0x000F

        sll $t2, $t1, 3                         # RB0 -> RE3
        andi $t2, $t2, 0x0008
        sll $t3, $t1, 1                         # RB1 -> RE2
        andi $t3, $t3, 0x0004
        srl $t4, $t1, 1                         # RB2 -> RE1
        andi $t4, $t4, 0x0002
        srl $t5, $t1, 3                         # RB3 -> RE0
        andi $t5, $t5, 0x0001

        or $t1, $t2, $t3
        or $t1, $t1, $t4
        or $t1, $t1, $t5                        # merge

        lw $t2, LATE($t0)
        andi $t2, $t2, 0xFFF0

        or $t2, $t1, $t2

        sw $t2, LATE($t0)

        j while

        jr $ra
