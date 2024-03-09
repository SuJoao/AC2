// PARTE II Ex6 and 7

#include <detpic32.h>

int main(){

    static const char disp7Scodes[] = { 0x3F, 0x06, 0x5B, 0x4F, 
                                        0x66, 0x6D, 0x7D, 0x07, 
                                        0x7F, 0x67, 0x77, 0x7C, 
                                        0x39, 0x5E, 0x79, 0x71};

    TRISB = TRISB | 0x000F;             // switch bit 0 to 3 (input)

    TRISD = TRISD & 0xFF9F;             // "select display"  bit 5 and 6 (output)
    TRISB = TRISB & 0x80FF;             // display bit 8 to 14 (output)

    LATD = (LATD & 0xFF9F) | 0x0020;    // LATD5 = 1; LATD6 = 0;
    //LATD = (LATD & 0xFF9F) | 0x0040;  // LATD5 = 0; LATD6 = 1;

    int value;

    while(1){

        value = disp7Scodes[PORTB & 0x000F] << 8;

        LATB = (LATB & 0x80FF) | value;

    }

    return 0;
}
