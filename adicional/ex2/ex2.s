# Ex 2
        
        .equ ADDR_BASE_HI,0xBF88    

        .equ TRISE,0x6100                 
        .equ PORTE,0x6110                  
        .equ LATE,0x6120   

        .equ inkey, 1
        .equ getchar, 2
        .equ readCoreTimer, 11
        .equ resetCoreTimer, 12

        .data
        .text
        .globl main

main:

        lui $t0, ADDR_BASE_HI

        lw $t1, TRISE($t0)
        andi $t1, $t1, 0xFFF0                   # config RE0-3 as output
        sw $t1, TRISE($t0)

        lw $t1, LATE($t0)
        andi $t1, $t1, 0xFFF0                   # turn off all LEDs
        sw $t1, LATE($t0)

while:

        li $v0, getchar                         # key = getChar()
        syscall
        move $t2, $v0

        lw $t1, LATE($t0)
        andi $t1, $t1, 0xFFF0                   # reset LEDs
        sw $t1, LATE($t0)

if1:    bne $t2, '0', if2                       # if(key == '0')
        
        lw $t1, LATE($t0)
        ori $t1, $t1, 0x0001                    # RE0 = 1 (LED0  active)
        sw $t1, LATE($t0)

        j endif


if2:    bne $t2, '1', if3                       # else if(key == '1')

        lw $t1, LATE($t0)
        ori $t1, $t1, 0x0002                    # RE1 = 1 (LED1 active)
        sw $t1, LATE($t0)

        j endif


if3:    bne $t2, '2', if4                       # else if(key == '2')

        lw $t1, LATE($t0)
        ori $t1, $t1, 0x0004                    # RE2 = 1  (LED2 active)
        sw $t1, LATE($t0)                               

        j endif


if4:    bne $t2, '3', else                      # else if(key == '3')

        lw $t1, LATE($t0)                 
        ori $t1, $t1, 0x0008                    # RE3 = 1 (LED3 active)
        sw $t1, LATE($t0)

        j endif


else:   
        lw $t1, LATE($t0)
        ori $t1, $t1, 0x000F                    # turn on all LEDs
        sw $t1, LATE($t0)

        li $v0, resetCoreTimer                  # resetCoreTimer()
        syscall

time:   li $v0, readCoreTimer
        syscall
        move $t2, $v0

        li $v0, inkey                           # key = inkey()
        syscall

        blt $t2, 20000000, time                 # while(resetCoreTimer() < 20000000)

        lw $t1, LATE($t0)
        andi $t1, $t1, 0xFFF0                   # turn off all LEDs
        sw $t1, LATE($t0)

endif:
        j while


        li $v0, 0

        jr $ra
