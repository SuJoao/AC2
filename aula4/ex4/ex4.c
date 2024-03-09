// PARTE II Ex1

#include <detpic32.h>

int main(){

    TRISB = TRISB & 0x80FF;                     // RB8 to RB14 = 0 (output) 
    TRISD = TRISD & 0xFF9F;                     // RD5 and RD6 = 0 (output)

    //LATD = (LATD & 0xFF9F) | 0x0020;          // LATD5 = 1; LATD6 = 0;
    LATD = (LATD & 0xFF9F) | 0x0040;            // LATD5 = 0; LATD6 = 1;


    while(1){

        char c = getChar();

        if(c == 'a') LATB = (LATB & 0x80FF) | 0x0100;
        if(c == 'g') LATB = (LATB & 0x80FF) | 0x4000;

    }


    return 0;
}
