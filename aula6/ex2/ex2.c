// Ex 2

#include <detpic32.h>
#define N 1

int main(){

    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4= 0; 
    AD1CON1bits.SSRC = 7; 
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16; 
    AD1CON2bits.SMPI = N-1; 
    AD1CHSbits.CH0SA = 4; 
    AD1CON1bits.ON = 1;

    TRISD = TRISD & 0xF7FF;         // RD11 as output 

    volatile int aux;

    while(1){

        AD1CON1bits.ASAM = 1;
        LATD = LATD | 0x0800;       // LATD11 = 1

        while(IFS1bits.AD1IF == 0);

        LATD = LATD & 0xF7FF;       // reset LATD11

        aux = ADC1BUF0;

        IFS1bits.AD1IF = 0;

    }

    return 0;
}
