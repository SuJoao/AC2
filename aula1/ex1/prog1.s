#   int main(void){
#       printStr("AC2 – Aulas praticas\n");
#
#       return 0;
#   }


        .equ PRINT_STR,8
        .data
msg:    .asciiz "AC2 – Aulas praticas\n"
        .text
    
        .globl main

main: 
        la $a0,msg
        li $v0,PRINT_STR                # printStr("AC2 – Aulas praticas\n");
        syscall

        li $v0,0                        # return 0;

        jr $ra
        