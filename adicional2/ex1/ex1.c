#include <detpic32.h>


void send2displays(unsigned char value);
unsigned char toBCD(unsigned char value);

volatile int value;

int main(){

    // config LEDs (RE0 - RE3) as output
    TRISE = TRISE & 0xFFF0;
    LATE = LATE & 0xFFF0;

    // config display as output
    TRISB = TRISB & 0x80FF;

    // config display select as output
    TRISD = TRISD & 0xFF9F;
    LATD = LATD & 0xFF9F;

    // config T2 (100hz)
    T2CONbits.TCKPS = 2;
    PR2 = 49999;
    TMR2 = 0;
    T2CONbits.TON = 0;

    // config T2 interrupt
    IPC2bits.T2IP = 1;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;

    EnableInterrupts();

    unsigned char key;
    unsigned int displayActive = 0;

    while(1){

        if(displayActive == 0){
            key = getChar();
        }else{
            do{
                key = inkey();
            }while(key == 0);
        }

        LATE = LATE & 0xFFF0;
        displayActive = 1;
        T2CONbits.TON = 1;

        if(key == '0'){
            LATE = LATE | 0x0001;
            value = 0;
        }else if(key == '1'){
            LATE = LATE | 0x0002;
            value = 1;
        }else if(key == '2'){
            LATE = LATE | 0x0004;
            value = 2;
        }else if(key == '3'){
            LATE = LATE | 0x0008;
            value = 3;
        }else{
            LATE = LATE | 0x000F;
            value = 0xFF;

            resetCoreTimer();
            while(readCoreTimer() < 20000000){
                key = inkey();
            }
            
            displayActive = 0;
            TMR2 = 0;
            T2CONbits.TON = 0;

            // reset LEDs
            LATE = LATE & 0xFFF0;
            // disable display
            LATD = LATD & 0xFF9F;
        }
    }
    return 0;
}


void _int_(8) isr_T2(void){

    if(value == 0xFF){
        send2displays(0xFF);
    }else{
        unsigned char bcd = toBCD(value);
        send2displays(bcd);
    }

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
