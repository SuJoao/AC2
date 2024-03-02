# PARTE 2       Ex 5)

# Contador Johnson de 4 bits, 1.5 Hz; 

        .equ ADDR_BASE_HI,0xBF88        

        .equ TIME, 12666666             # 1.5hz [10M ; 20M] -> [2hz ; 1hz]

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

        li $t2, 0                       # counter = 1

while:
        lw $t1, LATE($t0)               # read latE
        andi $t1, $t1, 0xFFE1           # reset bit1 bit2 bit3 bit4 = 0
        sll $t3, $t2, 1                 # LED "position"
        or $t1, $t1, $t3                # merge
        sw $t1, LATE($t0)               # write

        li $v0, RESET_CORE_TIMER        # RESET_CORE_TIMER()
        syscall

wait:   li $v0, READ_CORE_TIMER         # $v0 = READ_CORE_TIMER()
        syscall

        blt $v0,TIME, wait              # while(READ_CORE_TIMER() < time)   1.5hz


        srl $t3, $t2, 3                 # temp = counter >> 3 (bit 3 -> bit 0)
        xori $t3, $t3, 0x0001           # negate bit 0
        andi $t3, $t3, 0x0001           # Reset all bits except bit 0

        sll $t2, $t2, 1                 # count = count << 1

        or $t2, $t2, $t3                # merge count and temp

        andi $t2,$t2,0x000F             # up counter MOD 16

        j while

        jr $ra
