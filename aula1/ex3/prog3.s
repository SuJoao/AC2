#   int main(void){
#       char c;
#       int cnt = 0;
#
#       do{
#           c = inkey();
#           if( c != 0 )
#               putChar( c );
#           else
#               putChar('.');
#           cnt++;
#       } while( c != '\n' );
#       printInt(cnt, 10);
#       return 0;
#   }


# mapa de fds
# $t0 = cnt
# $t1 = c

        .equ inkey, 1
        .equ putChar, 3
        .equ printInt, 6
        .data
        .text
        .globl main

main:

        li $t0, 0               #  cnt = 0

do:     
        li $v0, inkey           # $v0 = inKey()
        syscall

        move $t1, $v0           # c = inKey()


if:     beq $t1, 0, else        # if(c != 0)

        move $a0, $t1       
        li $v0, putChar         # putChar(c)
        syscall

        j endif  
else:

        li $a0, '.'
        li $v0, putChar         # putChar('.')
        syscall

endif:

        addiu $t0, $t0, 1       # cnt++

while:  bne $t1, '\n', do       # while(c != '\n')

        move $a0, $t0
        li $a1, 10 
        li $v0, printInt        # printInt(cnt, 10)
        syscall

        li $v0, 0               # return 0

        jr $ra
