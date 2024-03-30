// Ex4

#include <detpic32.h>

void send2displays(unsigned char value);

unsigned char toBCD(unsigned char value); 


int main(){

    // LEDs as output
    TRISE = TRISE & 0xFFF0;

    // Select display as output
    TRISD = TRISD & 0xFF9F;

    // Display as output
    TRISB = TRISB & 0x80FF;

    // Reset LEDs
    LATE = LATE & 0xFFF0;

    // Disable display
    LATD = LATD & 0xFF9F;

    char key;
    unsigned int value = 0;
    unsigned int displayActive = 0;

    while(1){

        unsigned int i = 0;

        if(displayActive == 0){
            key = getChar();

        }else{
            do{
                key = inkey();

                unsigned int bcd = toBCD(value);
                send2displays(bcd);

                resetCoreTimer();
                while(readCoreTimer() < 200000);            // Refresh rate 100hz

            }while(key == 0);
        }

        displayActive = 1;

        // Reset LEDs
        LATE = LATE & 0xFFF0;

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

            // Turn on all LEDs and Display 'FF' (1s)

            // Turn on LEDs
            LATE = LATE | 0x000F;

            // Display 'FF'
            do{
                send2displays(0xFF);

                resetCoreTimer();
                while(readCoreTimer() < 200000);            // Refresh rate 100hz

                // Ignore all keys
                key = inkey();

            }while(++i < 100);                              // Display active (1s)

            // Reset LEDs
            LATE = LATE & 0xFFF0;

            // Disable display
            LATD = LATD & 0xFF9F;

            displayActive = 0;
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
