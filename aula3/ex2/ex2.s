# PARTE 1       Ex 1) e Ex 2)

        .equ ADDR_BASE_HI,0xBF88


        .equ TRISB,0x6040           # TRISB address: 0xBF886040
        .equ PORTB,0x6050           # PORTB address: 0xBF886050
        .equ LATB, 0x6060           # LATB  address: 0xBF886060

        .equ TRISE,0x6100           # TRISE address: 0xBF886100
        .equ PORTE,0x6110           # PORTE address: 0xBF886110
        .equ LATE, 0x6120           # LATE  address: 0xBF886120

        .equ TRISD,0x60C0           # TRISE address: 0xBF8860C0 
        .equ PORTD,0x60D0           # PORTE address: 0xBF8860D0
        .equ LATD, 0x60E0           # LATE  address: 0xBF8860E0

        .data
        .text
        .globl main
main:

        lui $t0, ADDR_BASE_HI       # $t0 = 0xBF880000

        lw $t1, TRISD($t0)          # read trisB
        ori $t1, $t1, 0x0001        # trisB0 = 1        (input)
        sw $t1, TRISD($t0)          # write tristB

        lw $t1, TRISE($t0)          # read = trisE
        andi $t1, 0xFFFE            # trisE0 = 0        (output)
        sw $t1, TRISE($t0)          # write tristE


while:

        lw $t1, PORTD($t0)          # read portB
        andi $t1, $t1, 0x0100       # Reset all bits except bit 0
        srl $t1, $t1, 8             # bit8 -> bit0

        lw $t2, LATE($t0)           # write latE
        andi $t2, $t2, 0xFFFE       # reset bit 0

        or $t2, $t2, $t1            # merge

        sw $t1, LATE($t0)           # write latE

        j while


        jr $ra



