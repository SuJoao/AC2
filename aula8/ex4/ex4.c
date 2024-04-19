// Parte 1 ex3

#include <detpic32.h>

int main(){

    // T3 config
    // 25hz -> Kpre = 4 ; 50hz -> Kpre = 3 
    T3CONbits.TCKPS = 3;
    PR3 = 49999;
    TMR3 = 2;
    T3CONbits.TON = 1;

    // T3 interrupt
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    // T1 config
    T1CONbits.TCKPS = 2;
    PR1 = 62499;
    TMR1 = 0;
    T1CONbits.TON = 1;

    // T1 interrupt
    IPC1bits.T1IP = 1;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;

    EnableInterrupts();

    while(1);

    return 0;
}


void _int_(12) isr_T3(void){

    putChar('3');

    IFS0bits.T3IF = 0;
}

void _int_(4) isr_T1(void){

    putChar('1');

    IFS0bits.T1IF = 0;
}
