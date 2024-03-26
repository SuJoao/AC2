// Ex 1

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

    while(1){
        AD1CON1bits.ASAM = 1;

        while(IFS1bits.AD1IF == 0);

        printInt(ADC1BUF0, 16 | 3 << 16);
        putChar('\n');

        IFS1bits.AD1IF = 0;
    }


    return 0;
}
