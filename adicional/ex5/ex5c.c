// Ex 5 c)

#include <detpic32.h>

void send2displays(unsigned char value);

unsigned char toBCD(unsigned char value) ;

int main(){

    // Select display as output
    TRISD = TRISD & 0xFF9F;
    // Display as output
    TRISB = TRISB & 0x80FF;


    unsigned int counter = 0;
    unsigned freq = 10;
    unsigned int cycles = 2000000;
    unsigned char key;
    unsigned int i;
    unsigned char bcd = 0x10;
    
    while(1){

        i = 0;

        key = inkey();

        if(key == '0'){
            freq = 2 * (1 + 0);
            cycles = 10000000;

        }else if(key == '1'){
            freq = 2 * (1 + 1);
            cycles = 5000000;

        }else if(key == '2'){
            freq = 2 * (1 + 2);
            cycles = 3333333;
            
        }else if(key == '3'){
            freq = 2 * (1 + 3);
            cycles = 2500000;

        }else if (key == '4'){
            freq = 2 * (1 + 4);
            cycles = 2000000;

        }else if(key == '\n'){
            printInt(counter, 10 | 2 << 16);
            printStr(", ");
            printInt(freq, 10 | 1 << 16);
            printStr(" Hz \r");

            //printf(", %.2d Hz \r", freq);

            bcd = toBCD(freq);

        } else{
            printInt(counter, 10 | 2 << 16);
            putChar('\r');
        }

        do{
            send2displays(bcd);

            resetCoreTimer();
            while(readCoreTimer() < 400000);            // refresh rate 50hz

        }while(++i < cycles / 400000);

        counter = (counter + 1) % 100;
        
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
