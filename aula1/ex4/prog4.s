#int main(void){
#    int value;
#    while(1){
#        printStr("\nIntroduza um inteiro (sinal e módulo): ");
#        value = readInt10();
#        printStr("\nValor em base 10 (signed): ");
#        printInt10(value);
#        printStr("\nValor em base 2: ");
#        printInt(value, 2);
#        printStr("\nValor em base 16: ");
#        printInt(value, 16);
#        printStr("\nValor em base 10 (unsigned): ");
#        printInt(value, 10);
#        printStr("\nValor em base 10 (unsigned), formatado: ");
#        printInt(value, 10 | 5 << 16); // ver nota de rodapé 3
#    }
#    return 0;
#}

# mapa de fds
# $t0 = value


        .equ readInt10, 5
        .equ printInt10, 7
        .equ printStr, 8
        .equ printInt, 6
        .equ putChar, 3
        .data

msg1:   .asciiz "\nIntroduza um inteiro (sinal e módulo): " 
msg2:   .asciiz "\nValor em base 10 (signed): "
msg3:   .asciiz "\nValor em base 2: "
msg4:   .asciiz "\nValor em base 16: "
msg5:   .asciiz "\nValor em base 10 (unsigned): "
msg6:   .asciiz "\nValor em base 10 (unsigned), formatado: "
        .text
        .globl main

main:   


while:  

        la $a0, msg1
        li $v0, printStr                # printStr(msg1)
        syscall

        li $v0, readInt10               # readInt10()
        syscall

        move $t0, $v0                   # value = readInt10()

        la $a0, msg2
        li $v0, printStr                # printStr(msg2)
        syscall

        move $a0, $t0
        li $v0, printInt10              # printInt10(value)
        syscall

        la $a0, msg3
        li $v0, printStr                # printStr(msg3)
        syscall

        move $a0, $t0
        li $a1, 2
        li $v0, printInt                # printInt(value, 2)
        syscall

        la $a0, msg4
        li $v0, printStr                # printStr(msg4)
        syscall

        move $a0, $t0
        li $a1, 16
        li $v0, printInt                # printInt(value, 16)
        syscall

        la $a0, msg5
        li $v0, printStr                # printStr(msg5)
        syscall

        move $a0, $t0
        li $a1, 10      
        li $v0, printInt                # printInt(value , 10)
        syscall

        la $a0, msg6
        li $v0, printStr                # printInt(msg6)
        syscall

        li $t1, 5                       # temp = 5
        sll $t1, $t1, 16                # temp = 5 << 16
        ori $t1, $t1, 10                # temp = 10 | (5 << 16)

        move $a0, $t0
        move $a1, $t1
        li $v0, printInt                # printInt(value, temp)
        syscall

        li $a0, '\n'
        li $v0, putChar                 # putChar('\n')
        syscall

        j while

        li $v0, 0                       # return 0

        jr $ra
