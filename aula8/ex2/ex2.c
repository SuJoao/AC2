// Parte 1 ex2

#include <detpic32.h>

int main(){

    // T3 config
    T3CONbits.TCKPS = 7;
    PR3 = 39062;
    TMR3 = 0;
    T3CONbits.TON = 1;

    // T3 interrupt
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    EnableInterrupts();

    while(1);

    return 0;
}


void _int_(12) isr_T3(void){

    putChar('.');
    IFS0bits.T3IF = 0;

}
