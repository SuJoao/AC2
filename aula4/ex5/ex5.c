// PARTE II Ex2, 3 and 4 

#include <detpic32.h>

int main() {

    unsigned int segment;
    
    TRISB = TRISB & 0x80FF;                     // display bit 8 to 14 (output)

    TRISD = TRISD & 0xFF9F;                     // "select display"  bit 5 and 6 (output)
    LATD = (LATD & 0xFF9F) | 0x0040;            // LATD5 = 0; LATD6 = 1;

    while (1) {
        segment = 1;

        for (int i = 0; i < 7; i++){

            LATB = (LATB & 0x80FF)| (segment << 8);

            resetCoreTimer();
            while(readCoreTimer() < 2000000);

            segment = segment << 1; 

        }
        LATD = LATD ^ 0x0060;                   // negate bit 5 and 6
    }

    return 0;
}

// 2hz = 10 000 000
// 10 hz = 2 000 000
// 50hz = 400 000
// 100 hz = 200 000
