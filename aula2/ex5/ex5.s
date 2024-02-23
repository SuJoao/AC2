# PARTE 2       Ex 4)

        .equ K, 20000
        .equ IN_KEY, 1
        .equ GET_CHAR, 2
        .equ PUT_CHAR, 3
        .equ PRINT_INT, 6
        .equ READ_CORE_TIMER, 11
        .equ RESET_CORE_TIMER, 12
        
        .data
        .text
        .globl main

# mapa de fds
# $s0 = cnt1
# $s1 = cnt5
# $s2 = cnt10
# $s3 = ms

main:

        addiu $sp, $sp, -20
        sw $ra, 0($sp)
        sw $s0, 4($sp)
        sw $s1, 8($sp)
        sw $s2, 12($sp)
        sw $s3, 16($sp)


        li $s0, 0                   # cnt1 = 0
        li $s1, 0                   # cnt5 = 0
        li $s2, 0                   # cnt10 = 0

        li $s3, 100                 # ms = 100

while:  

        li $v0, IN_KEY              # key = inKey()
        syscall

if3:    bne $v0, 'n', endIf3        # if(key == 'n')
        li $s3, 100                 # ms = 100
endIf3:


if4:    bne $v0, 'a', endIf4        # if(key == 'a')
        li $s3, 50                  # ms = 50
endIf4:


if5:    bne $v0, 's', endIf5        # if(key == 's')

while3: beq $v0, 'r', endWhile3     # while(key  != 'r')
        
        li $v0, GET_CHAR            # key = getChar()
        syscall

        j while3
endWhile3:

endIf5:


if6:    bne $v0, 'r', endIf6        # if(key == 'r')
        li $v0, IN_KEY              # key = inkey()
        syscall
endIf6:


        li $a0, '\r'
        li $v0, PUT_CHAR            # putChar('\r')
        syscall

        move $a0, $s0
        li $a1, 0x0005000A
        li $v0, PRINT_INT           # printInt(cnt1, 10 | 5 << 16)
        syscall

        li $a0, '\t'
        li $v0, PUT_CHAR            # putChar('\t')
        syscall

        move $a0, $s1
        li $a1, 0x0005000A
        li $v0, PRINT_INT           # printInt(cnt5, 10 | 5 << 16)
        syscall

        li $a0, '\t'
        li $v0, PUT_CHAR            # putChar('\t')
        syscall

        move $a0, $s2
        li $a1, 0x0005000A
        li $v0, PRINT_INT           # printInt(cnt5, 10 | 5 << 16)
        syscall


        move $a0, $s3
        jal delay                   # delay(ms)

        addi $s2, $s2, 1            # cnt10++


        rem $t0, $s2, 2             # temp = cnt10 % 2
if:     bne $t0, 0, endIf           # if(cnt10 % 2 == 0)

        addi $s1, $s1, 1            # cnt5++

endIf:

        rem $t0, $s2, 10            # temp = cnt10 % 10
if2:    bne $t0, 0, endIf2          # if(cnt10 % 10 == 0)

        addi $s0, $s0, 1            # cnt1++

endIf2:

        j while


        
        lw $ra, 0($sp)
        lw $s0, 4($sp)
        lw $s1, 8($sp)
        lw $s2, 12($sp)
        lw $s3, 16 ($sp)
        addiu $sp, $sp, 20

        jr $ra





delay:

        li $v0, RESET_CORE_TIMER        # resetCoreTimer()
        syscall

while2:  

        li $v0, READ_CORE_TIMER         # $v0 = readCoreTimer()
        syscall

        mul $t0, $a0, K                 # K * ms
        
        bge $v0, $t0, endWhile2         # while(readCoreTimer() < K * ms)

        j while2

endWhile2:

        jr $ra
        