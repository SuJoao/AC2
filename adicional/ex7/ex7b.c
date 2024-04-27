// Ex7 a)

#include <detpic32.h>

#define N 1

int main(){

    // A/D config
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0; 
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16; 
    AD1CON2bits.SMPI = N-1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1; 

    // sw as input
    TRISB = TRISB | 0x000F;

    unsigned int freq;

    while(1){

        printStr("DS=");
        putChar(((PORTB & 0x0008) >> 3) + '0');
        putChar(((PORTB & 0x0004) >> 2) + '0');
        putChar(((PORTB & 0x0002) >> 1) + '0');
        putChar((PORTB & 0x0001) + '0');
        putChar('\r');

        AD1CON1bits.ASAM = 1;

        while(IFS1bits.AD1IF == 0);

        unsigned int value = ADC1BUF0;

        IFS1bits.AD1IF = 0;

        freq = ((value*4)/1023) + 1; 

        resetCoreTimer();
        while(readCoreTimer() < 20000000/freq);
    }

    return 0;
}
