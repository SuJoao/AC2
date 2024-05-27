#include <detpic32.h>

void send2displays(unsigned char value);
unsigned char toBCD(unsigned char value);

volatile unsigned int count = 0;

int main(){

    // config display as output
    TRISB = TRISB & 0x80FF;

    // config display select as output
    TRISD = TRISD & 0xFF9F;

    // config T1 (10hz)
    T1CONbits.TCKPS = 2;
    PR1 = 31249; 
    TMR1 = 0; 
    T1CONbits.TON = 1;

    // config T1 interrupt
    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1; 
    IFS0bits.T1IF = 0; 

    // config T2 (50hz)
    T2CONbits.TCKPS = 3;
    PR2 = 49999; 
    TMR2 = 0; 
    T2CONbits.TON = 1;

    // config T2 interrupt
    IPC2bits.T2IP = 2;
    IEC0bits.T2IE = 1; 
    IFS0bits.T2IF = 0; 

    EnableInterrupts();

    while(1);


    return 0;
}

// increment count (10hz)
void _int_(4) isr_T1(void){

    printInt(count, 0x00020010);
    putChar('\n');
    count = (count + 1) % 100;

    IFS0bits.T1IF = 0; 
}


// refresh rate (50hz)
void _int_(8) isr_T2(void){

    unsigned char bcd = toBCD(count);
    send2displays(bcd);

    IFS0bits.T2IF = 0; 
}


void send2displays(unsigned char value) {

    static const char disp7Scodes[] = { 0x3F, 0x06, 0x5B, 0x4F, 
                                        0x66, 0x6D, 0x7D, 0x07, 
                                        0x7F, 0x67, 0x77, 0x7C, 
                                        0x39, 0x5E, 0x79, 0x71 };

    static char displayFlag = 0;

    unsigned char display_low = value & 0x0F;
    unsigned char display_high = value >> 4;

    if (displayFlag == 0) {
        LATD = (LATD & 0xFF9F) | 0x0020;                       
        LATB = (LATB & 0x80FF) | (disp7Scodes[display_low] << 8);
    } else {
        LATD = (LATD & 0xFF9F) | 0x0040;                       
        LATB = (LATB & 0x80FF) | (disp7Scodes[display_high] << 8);
    }
    displayFlag = displayFlag ^ 1;
}


unsigned char toBCD(unsigned char value) {

    return ((value / 10) << 4) + (value % 10);
}
