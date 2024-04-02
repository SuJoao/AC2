# Ex 6 b)

# mapa de fds
# counter : $t0
# freq = $t1
# cycles = $t2
# key = $t3


        .equ inkey, 1
        .equ putChar, 3
        .equ printStr, 8
        .equ printInt, 6
        .equ readCoreTimer, 11
        .equ resetCoreTimer, 12

        .data
str1:   .asciiz ", "
str2:   .asciiz " Hz \r"
        .text
        .globl main

main:

        li $t0, 0                       # counter = 0
        li $t1, 10                      # freq = 10
        li $t2, 2000000                 # cycles = 2000000

while:

        li $v0, 1                       # $v0 = inkey()
        syscall
        move $t3, $v0                   # key = $v0

if:     bne $t3, '0', elif2             # if(key == '0')

        li $t1, 2                       # freq = 2
        li $t2, 10000000                # cycles = 10000000

        j endif

elif2:  bne $t3, '1', elif3             # if(key == '1')

        li $t1, 4                       # freq = 4
        li $t2, 5000000                 # cycles = 5000000                 

        j endif

elif3:  bne $t3, '2', elif4             # if(key == '2')

        li $t1, 6                       # freq = 6
        li $t2, 3333333                 # cycles = 3333333                 

        j endif

elif4:  bne $t3, '3', elif5             # if(key == '3')

        li $t1, 8                       # freq = 8
        li $t2, 2500000                 # cycles = 2500000

        j endif

elif5:  bne $t3, '4', elif6             # if(key == '4')

        li $t1, 10                      # freq = 10
        li $t2, 2000000                 # cycles = 2000000

        j endif

elif6:  bne $t3, '\n', else             # if(key == '\n')

        move $a0, $t0                  
        li $a1, 0x0002000A      
        li $v0, printInt                # printInt(counter, 10 | 2 << 16); 
        syscall

        la $a0, str1
        li $v0, printStr                # printStr(", ")
        syscall

        move $a0, $t1                  
        li $a1, 0x0001000A      
        li $v0, printInt                # printInt(counter, 10 | 1 << 16); 
        syscall

        la $a0, str2
        li $v0, printStr                # printStr(" Hz \r")
        syscall

        j endif

else:   
        move $a0, $t0                 
        li $a1, 0x0002000A      
        li $v0, printInt                # printInt(counter, 10 | 2 << 16); 
        syscall

        li $a0, '\r'
        li $v0, putChar                 # putChar('\r');
        syscall

endif:

        li $v0, resetCoreTimer          # resetCoreTimer() 
        syscall

wait:   li $v0, readCoreTimer
        syscall

        blt $v0, $t2, wait              # while(readCoreTimer() < cycles)

        addi $t0, $t0, 1
        rem $t0, $t0, 100               # counter = (counter + 1) % 100

        j while

        li $v0, 0                       # return 0;

        jr $ra
