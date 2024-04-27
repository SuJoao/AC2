// Parte 2 Ex1

#include <detpic32.h>

int main(){

    // T3 config (100hz)
    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T3CONbits.TON = 1;

    // OC1 config 
    OC1CONbits.OCM = 6; 
    OC1CONbits.OCTSEL = 1;
    OC1RS = 12500;
    OC1CONbits.ON = 1;
 
    while(1);
    
    return 0;
}
