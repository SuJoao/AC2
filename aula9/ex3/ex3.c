// Parte 2 Ex3

#include <detpic32.h>

void setPWM(unsigned int dutyCycle);

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
 
    setPWM(10);
    //setPWM(65);
    //setPWM(80);

    while(1);
    
    return 0;
}


void setPWM(unsigned int dutyCycle){

    OC1RS = (49999 * dutyCycle) / 100;
}
