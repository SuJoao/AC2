# Ex 6 a)

        .equ printInt, 6
        .equ putChar, 3
        .equ readCoreTimer, 11
        .equ resetCoreTimer, 12

        .data
        .text
        .globl main

main:

        li $t0, 0                       # counter = 0

while:

        move $a0, $t0
        li $a1, 0x0002000A
        li $v0, printInt                # printInt(counter, 10 | 2 << 16)
        syscall

        li $a0, '\r'
        li $v0, putChar                 # putChar('\r')
        syscall

        li $v0, resetCoreTimer          # resetCoreTimer()
        syscall

wait:   li $v0, readCoreTimer
        syscall

        blt $v0, 2000000, wait          # while(readCoreTimer() < 2000000)

        addi $t0, $t0, 1
        rem $t0, $t0, 100               # counter = (counter + 1) % 100

        j while

        li $v0, 0                       # return 0;

        jr $ra


