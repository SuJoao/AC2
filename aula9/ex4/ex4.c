// Parte 2 Ex5

#include <detpic32.h>

void setPWM(unsigned int dutyCycle);

int main(){

    // config LED11 (RC14) as output
    TRISC = TRISC & 0xBFFF;
    
    // T3 config (100hz)
    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T3CONbits.TON = 1;

    // OC1 config 
    OC1CONbits.OCM = 6; 
    OC1CONbits.OCTSEL = 1;
    OC1RS = 125;
    OC1CONbits.ON = 1;

    setPWM(15);

    while(1){
        LATC = (LATC & 0xBFFF) | ((PORTD & 0x0001) << 14); 
    }

    return 0;
}


void setPWM(unsigned int dutyCycle){

    OC1RS = (49999 * dutyCycle) / 100;
}
