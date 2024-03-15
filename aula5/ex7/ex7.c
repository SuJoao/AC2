// PARTE II Ex 4

#include <detpic32.h>

void send2displays(unsigned char value);

unsigned char toBCD(unsigned char value);

int main(void) {

    TRISB = TRISB & 0x80FF;                                 // configure RB8-RB14 as outputs
    TRISD = TRISD & 0xFF9F;                                 // configure RD5-RD6 as outputs

    TRISE = TRISE & 0xFF00;                                 // configure RE0-RE7 as outputs

    TRISB = TRISB | 0x0001;                                 // configure RB0 as input
    
    TRISC = TRISC & 0xBFFF;                                 // configure RC14 as output

    unsigned int counter = 0;
    unsigned int time = 20;                                          
    unsigned int active = 0;

    while (1) {

        unsigned int i = 0;

        do {

            unsigned char bcd = toBCD(counter);

            send2displays(bcd);

            LATE = (LATE & 0xFF00) | (bcd & 0x00FF);

            if(active != 0){
                active--;
                LATC = LATC | 0x4000;
            }else{
                LATC = LATC & 0xBFFF;
            }

            resetCoreTimer();
            while(readCoreTimer() < 200000);                // refresh rate 100hz 

        } while (++i < time);
        
        unsigned int sw = PORTB & 0x0001;
        
        if (sw == 1) {
            time = 20;
            //counter = counter < 59 ? counter + 1 : 0;
            counter = (counter + 1) % 60;

            if(counter == 59) active = 25;

        } else {
            time = 50;
            //counter = counter > 0 ? counter - 1 : 59;
            counter = (counter + 59) % 60;

            if(counter == 0) active = 10; 
        }

        
    }

    return 0;
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
        LATD = (LATD & 0xFF9F) | 0x0020;                         // RB6 = 0; RB5 = 1;     low active
        //LATB = (LATB & 0x80FF) | (disp7Scodes[value & 0x0F] << 8);
        LATB = (LATB & 0x80FF) | (disp7Scodes[display_low] << 8);
    } else {
        LATD = (LATD & 0xFF9F) | 0x0040;                         // RB6 = 1; RB5 = 0;     high active
        //LATB = (LATB & 0x80FF) | (disp7Scodes[value >> 4] << 8);
        LATB = (LATB & 0x80FF) | (disp7Scodes[display_high] << 8);
    }
    displayFlag = displayFlag ^ 1;
}



unsigned char toBCD(unsigned char value) {

    return ((value / 10) << 4) + (value % 10);
}
