// Ex3 b)

#include <detpic32.h>

int main(){

    // LEDs as output
    TRISE = TRISE & 0xFFF0;

    // Reset LEDs
    LATE = LATE & 0xFFF0;

    char key;

    while(1){

        key = getChar();

        // Reset LEDs
        LATE = LATE & 0xFFF0;

        if(key == '0'){
            LATE = LATE | 0x0001;

        }else if(key == '1'){
            LATE = LATE | 0x0002;

        }else if(key == '2'){
            LATE = LATE | 0x0004;

        }else if(key == '3'){
            LATE = LATE | 0x0008;

        }else{
            // Turn on LEDs
            LATE = LATE | 0x000F;

            // wait 1s
            resetCoreTimer();
            while(readCoreTimer() < 20000000){
                // Ignore all keys
                key = inkey();
            }

            // Reset LEDs
            LATE = LATE & 0xFFF0;
        }
    }
    return 0;
}
