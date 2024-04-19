// Parte 2 ex1

#include <detpic32.h>

int main(){

    // config LED0 as output
    TRISE = TRISE & 0xFFFE;

    // reset LED0
    LATE = LATE & 0xFFFE;

    // T2 config (timer disabled)
    T2CONbits.TCKPS = 7;
    PR2 = 39062;
    TMR2 = 0;
    T2CONbits.TON = 0;

    // T2 interrupt
    IPC2bits.T2IP = 2;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;

    // config RD8 as input
    TRISD = TRISD | 0x0100;

    // INT1 interrupt
    IFS0bits.INT1IF = 0;
    IEC0bits.INT1IE = 1;
    IPC1bits.INT1IP = 1;
    INTCONbits.INT1EP = 0;

    EnableInterrupts();
    
    while(1);

    return 0;
}

void _int_(8) isr_T2(void){
    
    static unsigned int flag = 1;

    // wait 3s (LED on)
    if(flag % 6 == 0){
        // reset LED
        LATE = LATE & 0xFFFE;
        // disable timer
        T2CONbits.TON = 0;
    }
    flag++;

    IFS0bits.T2IF = 0;
}

void _int_(7) isr_INT1(void){

    // LED on
    LATE = LATE | 0x0001;

    // activate timer
    TMR2 = 0;
    T2CONbits.TON = 1;

    IFS0bits.INT1IF = 0;
}
