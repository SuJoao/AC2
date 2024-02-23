# PARTE 1       Ex 1)
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

# a) 
# 20 Mhz = 50 ns
# 200 000 * 50 = 10 000 000 ns
# 10 000 000 ns = 10 000 us = 10 ms
# 10 ms = 100 hz


# mapa de fds
# counter = $t0

        .equ PUT_CHAR, 3
        .equ PRINT_INT, 6
        .equ READ_CORE_TIMER, 11
        .equ RESET_CORE_TIMER, 12

        .data
        .text
        .globl main

main:   

        li $t0, 0                       # counter = 0

while:  

        li $t1, 0x0004000A              # temp = 10 | 4 << 16 
        #li $t1, 4                      # temp = 4
        #sll $t1, $t1, 16               # temp = 4 << 16
        #ori $t1, $t1, 10               # temp = 10 | 4 << 16 

        
        move $a0, $t0
        move $a1, $t1   
        li $v0, PRINT_INT               # print_int(counter, 10 | 4 << 16)
        syscall

        li $a0, '\r'
        li $v0, PUT_CHAR
        syscall

        li $v0, RESET_CORE_TIMER        # resetCoreTimer()
        syscall

while2: 
        li $v0, READ_CORE_TIMER         # $v0 = readCoreTimer()
        syscall

        bge $v0, 200000000, endWhile2   # while(readCoreTimer() < 200000)

        j while2

endWhile2:

        addi $t0, $t0, 1                # counter++

        j while


        jr $ra     

# 100 hz = 200 000
# 10 hz = 2 000 000
# 5 hz = 4 000 000
# 1 hz = 20 000 000
