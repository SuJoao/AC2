##define UP 1
##define DOWN 0
#
#void wait(int);
#int main(void){
#
#    int state = 0;
#    int cnt = 0;
#    char c;
#    do{
#
#        putChar('\r');                  // Carriage return character
#        printInt( cnt, 10 | 3 << 16 );  // 0x0003000A: decimal w/ 3 digits
#        putChar('\t');                  // Tab character
#        printInt( cnt, 2 | 8 << 16 );   // 0x00080002: binary w/ 8 bits
#
#        wait(5);                        // wait 0.5s
#        c = inkey();
#        if( c == '+' )
#            state = UP;
#        if( c == '-' )
#            state = DOWN;
#        if( state == UP )
#            cnt = (cnt + 1) & 0xFF;      // Up counter MOD 256
#        else
#            cnt = (cnt - 1) & 0xFF;      // Down counter MOD 256
#
#    } while( c != 'q' );
#    return 0;
#}
#
#
#void wait(int ts){
#    int i;
#    for(i=0; i < 515000 * ts; i++); // wait approximately ts/10 seconds
#}

# mapa de fds
# $s0 = state
# $s1 = cnt
# $s2 = c
        .equ inkey, 1
        .equ getChar, 2
        .equ putChar, 3
        .equ printInt, 6
        .equ UP, 1
        .equ DOWN, 0
        .data
        .text
        .globl main

main:
        addiu $sp, $sp, -4      # guardar batatas
        sw $ra, 0($sp)


        li $s0, 0               # state = 0
        li $s1, 0               # cnt = 0 

do:     
        li $a0, '\r'
        li $v0, putChar         # putChar('\r')
        syscall

        li $t0, 3               # temp = 3
        sll $t0, $t0, 16        # temp = 3 << 16
        ori $t0, $t0, 10        # temp = 10 | (3 << 16)

        move $a0, $s1
        move $a1, $t0
        li $v0, printInt        # printInt(cnt, temp)
        syscall 

        li $a0, '\t'
        li $v0, putChar         # putChar('\t')
        syscall

        li $t0, 8               # temp = 8
        sll $t0, $t0, 16        # temp = 8 << 16
        ori $t0, $t0, 2         # temp = 2 | (8 << 16)

        move $a0, $s1
        move $a1, $t0
        li $v0, printInt        # printInt(cnt, temp)
        syscall

        li $a0, 5               
        jal wait                # wait(5)

        li $v0, inkey           # inkey()
        syscall
        move $s2, $v0           # c = inkey()


if:     bne $s2, 's', endif     # if(c == s)
        
        li $v0, getChar         # getChar         
        syscall 
        move $s2, $v0           # c = gerChar
endif:

if2:    bne $s2, '+', endif2    # if(c == '+')
        li $s0, UP              # state = UP
endif2:

if3:    bne $s2, '-', endif3    # if(c == '-')
        li $s0, DOWN            # state = DOWN
endif3:

if4:    bne $s2, 'r', endif4    # if(c ==  'r')
        li $s1, 0               # cnt = 0
endif4:


if5:    bne $s0, UP, else5      # if(state == UP)

        addi $s1, $s1, 1        # cnt = cnt + 1
        andi $s1, $s1, 0xFF     # cnt = (cnt + 1) & 0xFF

        j endif5

else5:                          # else
        addi $s1, $s1, -1       # cnt = cnt - 1 
        andi $s1, $s1, 0xFF     # cnt = (cnt - 1) & 0xFF

endif5:

while:  bne  $s2, 'q', do       # while(c != 'q')


        lw $ra, 0($sp)  
        addiu $sp, $sp, 4       # devolver batatas

        li $v0, 0               # return 0

        jr $ra



wait:

        li $t0, 0               # i = 0
        mul $t1, $a0, 515000


for:    bge $t0, $t1, endFor    # while(i < ts * 515000)


        addi $t0, $t0, 1        # i++
        j for           

endFor:
        jr $ra

