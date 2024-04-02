# Ex8

        .equ ADDR_BASE_HI,0xBF88    

        .equ TRISB,0x6040                  
        .equ PORTB,0x6050                  
        .equ LATB, 0x6060 

        .equ putChar, 3
        .equ printStr, 8
        .equ readCoreTimer, 11
        .equ resetCoreTimer, 12 

        .data
str:    .asciiz "DS="
        .text
        .globl main

main:

        lui $t0, ADDR_BASE_HI

        lw $t1, TRISB($t0)
        ori $t1, $t1, 0x000F
        sw $t1, TRISB($t0)                  # sw as input

while:

        la $a0, str
        li $v0, printStr                    # printStr("DS=")
        syscall

        lw $t1, PORTB($t0)
        
        andi $t2, $t1, 0x0008               # $t2 = PORTB & 0x0008
        srl $t2, $t2, 3                     # $t2 = PORTB & 0x0008) >> 3
        addi $t2, $t2, '0'                  # $t2 = ((PORTB & 0x0008) >> 3) + '0'

        andi $t3, $t1, 0x0004               # $t3 = PORTB & 0x0004
        srl $t3, $t3, 2                     # $t3 = (PORTB & 0x0004) >> 2
        addi $t3, $t3, '0'                  # $t3 = ((PORTB & 0x0004) >> 2) + '0'

        andi $t4, $t1, 0x0002               # $t4 = PORTB & 0x0002
        srl $t4, $t4, 1                     # $t4 = (PORTB & 0x0002) >> 1
        addi $t4, $t4, '0'                  # $t4 = ((PORTB & 0x0002) >> 1) + '0'

        andi $t5, $t1, 0x0001               # $t5 = PORTB & 0x0001
        addi $t5, $t5, '0'                  # $t5 = (PORTB & 0x0001) + '0'

        move $a0, $t2
        li $v0, putChar                     # putChar(((PORTB & 0x0008) >> 3) + '0')
        syscall

        move $a0, $t3
        li $v0, putChar                     # putChar(((PORTB & 0x0004) >> 2) + '0')
        syscall

        move $a0, $t4
        li $v0, putChar                     # putChar(((PORTB & 0x0002) >> 1) + '0')
        syscall

        move $a0, $t5
        li $v0, putChar                     # putChar((PORTB & 0x0001) + '0')
        syscall

        li $a0, '\r'
        li $v0, putChar                     # putChar('\r')
        syscall

        li $v0, resetCoreTimer              # resetCoreTimer()
        syscall

wait:   li $v0, readCoreTimer
        syscall

        blt $v0, 20000000, wait             # while(readCoreTimer() < 20000000)  

        j while


        li $v0, 1                           # return 0

        jr $ra
