// PARTE I Ex 1, 2

#include <detpic32.h>

void send2displays(unsigned char value);

int main(){

    TRISB = TRISB & 0x80FF;                                 // configure RB8-RB14 as outputs
    TRISD = TRISD & 0xFF9F;                                 // configure RD5-RD6 as outputs
    
    while(1){

        send2displays(0x15);

        resetCoreTimer();
        while(readCoreTimer() < 4000000);                   // wait 0.2s

    }

    return 0;
}

// send2displays incorreta

void send2displays(unsigned char value){


    static const char disp7Scodes[] = { 0x3F, 0x06, 0x5B, 0x4F, 
                                        0x66, 0x6D, 0x7D, 0x07, 
                                        0x7F, 0x67, 0x77, 0x7C, 
                                        0x39, 0x5E, 0x79, 0x71 };

    
    LATD = (LATD & 0xFF9F) | 0x0040;                         // RB6 = 1; RB5 = 0;     high active
    LATB = (LATB & 0x80FF) | (disp7Scodes[value >> 4] << 8);

    LATD = (LATD & 0xFF9F) | 0x0020;                         // RB6 = 0; RB5 = 1;     low active
    LATB = (LATB & 0x80FF) | (disp7Scodes[value & 0x0F] << 8);

}
