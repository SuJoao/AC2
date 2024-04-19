// Parte 2 ex1

#include <detpic32.h>

int main(){

    // config LED0 as output
    TRISE = TRISE & 0xFFFE;

    // reset LED0
    LATE = LATE & 0xFFFE;

    // config RD8 as input
    TRISD = TRISD | 0x0100;

    unsigned char key = 0;

    while(1){

        key = (PORTD & 0x0100) >> 8;

        if(key == 0){

            LATE = LATE | 0x0001;

            resetCoreTimer();
            while(readCoreTimer() < 60000000);

            LATE = LATE & 0xFFFE;
        }

    }
    return 0;
}
