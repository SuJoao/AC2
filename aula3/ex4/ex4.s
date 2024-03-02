# PARTE 2       Ex 3)

# Contador binário módulo 16 crescente/decrescente (sw RB3)

        .equ ADDR_BASE_HI,0xBF88

        .equ TIME, 10000000

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
        ori $t1, $t1, 0x0008            # bit3 = 1 (input)
        sw $t1, TRISB($t0)              # write

        li $t2, 0                       # counter = 0

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

        blt $v0,TIME, wait              # while(READ_CORE_TIMER() < time)   2hz = 0.5s


        lw $t1, PORTB($t0)              # read portB
        andi $t1, $t1, 0x0008           # Reset all bits except bit 3    (0000 0000 0000 1000)
    
if:     bne $t1, 8, else                # if(RB3 == 1)
        addi $t2,$t2, 1                 # count++

        j endif               
else:
        addi $t2,$t2,-1                 # count--
endif:
        andi $t2,$t2,0x000F             # up counter MOD 16

        j while

        jr $ra
