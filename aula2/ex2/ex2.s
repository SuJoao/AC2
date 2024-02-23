# PARTE 1       Ex 2)

# int main(void) { 
#     int counter = 0; 
#     while(1) { 
#         putChar('\r'); // cursor regressa ao inicio da linha no ecrã 
#         printInt(counter, 10 | 4 << 16); // Ver nota de rodapé 1
#         resetCoreTimer(); 
#         while(readCoreTimer() < 200000); 
#             counter++; 
#     } 
#     return 0; 
# }

        .equ K, 20000
        .equ PUT_CHAR, 3
        .equ PRINT_INT, 6
        .equ READ_CORE_TIMER, 11
        .equ RESET_CORE_TIMER, 12
        
        .data
        .text
        .globl main

# mapa de fds
# $s0 = counter

main:   

        addiu $sp, $sp, -4              # guardar batatas
        sw $ra, 0($sp)


        li $s0, 0                       # counter = 0

while:  

        li $t1, 0x0004000A               # temp = 10 | 4 << 16 
        #li $t1, 4                       # temp = 4
        #sll $t1, $t1, 16                # temp = 4 << 16
        #ori $t1, $t1, 10                # temp = 10 | 4 << 16 


        move $a0, $s0
        move $a1, $t1   
        li $v0, PRINT_INT               # print_int(counter, 10 | 4 << 16)
        syscall

        li $a0, '\r'
        li $v0, PUT_CHAR
        syscall

        li $a0, 1000                    # 1ms
        jal delay                       # delay(1)

        addi $s0, $s0, 1                # counter++

        j while

        lw $ra, 0($sp)
        addiu $sp, $sp, 4               # guardar batatas

        jr $ra  





#void delay(unsigned int ms){
#   resetCoreTimer();
#   while(readCoreTimer() < K * ms);
#}


delay:

        li $v0, RESET_CORE_TIMER        # resetCoreTimer()
        syscall

while2:  

        li $v0, READ_CORE_TIMER         # $v0 = readCoreTimer()
        syscall

        mul $t0, $a0, K                 # K * ms
        
        bge $v0, $t0, endWhile2         # while(readCoreTimer() < K * ms)

        j while2

endWhile2:

        jr $ra
