
# PARTE 2       Ex 1) Ex 2)

# a) Contador binário crescente de 4 bits (módulo 16), frequência de 1Hz
# b) Contador binário decrescente de 4 bits (módulo 16), fequência de 4Hz

        .equ ADDR_BASE_HI,0xBF88

        .equ TIME, 5000000              # 4hz

        .equ TRISB,0x6040               # TRISB address: 0xBF886040
        .equ PORTB,0x6050               # PORTB address: 0xBF886050
        .equ LATB, 0x6060               # LATB  address: 0xBF886060

        .equ TRISE,0x6100               # TRISE address: 0xBF886100
        .equ PORTE,0x6110               # PORTE address: 0xBF886110
        .equ LATE, 0x6120               # LATE  address: 0xBF886120

        .equ K, 20000
        .equ READ_CORE_TIMER, 11
        .equ RESET_CORE_TIMER, 12

        .data
        .text
        .globl main
main:

        lui $t0, ADDR_BASE_HI

        lw $t1, TRISE($t0)              # read trisE
        andi $t1, $t1, 0xFFE1           # bit1 bit2 bit3 bit4 = 0 (output)
        sw $t1, TRISE($t0)              # write

        lw $t1, TRISB($t0)              # read trisB
        ori $t1, $t1, 0x0002            # bit1 = 1 (input)
        sw $t1, TRISB($t0)              # write

        li $t2, 0                       # counter = 0

while:
        lw $t1, LATE($t0)               # read latE
        andi $t1, $t1, 0xFFE1           # reset bit1 bit2 bit3 bit4 = 0
        sll $t3, $t2, 1                 # LED "position"
        or $t1, $t1, $t3                # merge0
        sw $t1, LATE($t0)               # write

        li $v0, RESET_CORE_TIMER        # RESET_CORE_TIMER()
        syscall

wait:   li $v0, READ_CORE_TIMER         # $v0 = READ_CORE_TIMER()
        syscall

        blt $v0,TIME, wait              # while(READ_CORE_TIMER() < time)   4hz = 0.25s

        addi $t2,$t2,-1                 # count--
        andi $t2,$t2,0x000F             # up counter MOD 16


    j while

    jr $ra



# a) 1hz = 1s = TIME = 20 000 000

# b) down counter 4hz
#    counter-- 
#    4hz = 0,25s = TIME = 5 000 000




    
