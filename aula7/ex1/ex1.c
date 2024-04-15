// Parte 1 Ex1

#include <detpic32.h>
#define N 1

int main(){

    // A/D config
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4= 0; 
    AD1CON1bits.SSRC = 7; 
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16; 
    AD1CON2bits.SMPI = N-1; 
    AD1CHSbits.CH0SA = 4; 
    AD1CON1bits.ON = 1;

    IPC6bits.AD1IP = 2;             // priority
    IFS1bits.AD1IF = 0;             // reset flag 
    IEC1bits.AD1IE = 1;             // enable

    EnableInterrupts();

    AD1CON1bits.ASAM = 1;   

    while(1);

    return 0;
}

void _int_(27) isr_adc(){
    
    printInt(ADC1BUF0,  16 | 3 << 16);
    putChar('\n');

    AD1CON1bits.ASAM = 1;

    IFS1bits.AD1IF = 0;
}


