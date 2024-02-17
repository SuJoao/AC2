#int main(void)
#{
#    char c;
#    int cnt = 0;
#    do
#    {   
#        c = getChar();
#        putChar( c );
#        cnt++;
#    } while( c != '\n' );
#    printInt(cnt, 10);
#    return 0;
#}

# mapa de fds
# $t0 = cnt
# #t1 = c

        .equ getChar, 2
        .equ putChar, 3
        .equ printInt, 6
        .data
        .text
        .globl main

main:

        li $t0, 0               # cnt = 0

do:
        li $v0, getChar         # c = getChar()  
        syscall

        move $t1, $v0           # $t1 = c

        move $a0, $v0
        addiu $a0, $a0, 1
        li $v0, putChar         # putChar(c) 
        syscall

        addiu $t0, $t0, 1        # cnt++

while:  bne $t1, '\n', do       # while(c =! '\n')

        move $a0, $t0
        li $a1, 10
        li $v0, printInt        # printInt(cnt, 10)
        syscall

        li $v0, 0               # return 0

        jr $ra
