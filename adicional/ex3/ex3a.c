// Ex3 a)

#include <detpic32.h>

int main(){

    // LEDs as output
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    TRISEbits.TRISE3 = 0;

    // Reset LEDs
    LATEbits.LATE0 = 0;
    LATEbits.LATE1 = 0;
    LATEbits.LATE2 = 0;
    LATEbits.LATE3 = 0;

    char key;

    while(1){

        key =  getChar();

        // Reset LEDs
        LATEbits.LATE0 = 0;
        LATEbits.LATE1 = 0;
        LATEbits.LATE2 = 0;
        LATEbits.LATE3 = 0;

        if(key == '0'){
            LATEbits.LATE0 = 1;

        }else if(key == '1'){
            LATEbits.LATE1 = 1;

        }else if(key == '2'){
            LATEbits.LATE2 = 1;

        }else if(key == '3'){
            LATEbits.LATE3 = 1;

        }else{
            // Turn on LEDs
            LATEbits.LATE0 = 1;
            LATEbits.LATE1 = 1;
            LATEbits.LATE2 = 1;
            LATEbits.LATE3 = 1;

            // wait 1s
            resetCoreTimer();
            while(readCoreTimer() < 20000000){
                // Ignore all keys
                key = inkey();
            }

            // Reset LEDs
            LATEbits.LATE0 = 0;
            LATEbits.LATE1 = 0;
            LATEbits.LATE2 = 0;
            LATEbits.LATE3 = 0;
        }
    }
    return 0;
}
