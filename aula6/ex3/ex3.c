// Ex 3 e 4

#include <detpic32.h>
#define N 4


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

        int *p = (int*)(&ADC1BUF0);

        for(int i = 0; i < 16; i++){
            printInt(p[i*4], 16 | 4 << 16);
            putChar('\t');
        }

        putChar('\n');

        resetCoreTimer();
        while(readCoreTimer() < 20000000);

        IFS1bits.AD1IF = 0;
    }

    return 0;
}
