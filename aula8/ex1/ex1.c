// Parte 1 ex2

#include <detpic32.h>

int main(){

    T3CONbits.TCKPS = 7;
    PR3 = 39062; 
    TMR3 = 0; 
    T3CONbits.TON = 1; 

    while(1){

        while(IFS0bits.T3IF == 0);
        IFS0bits.T3IF = 0;

        putChar('.');

    }
    return 0;
}
