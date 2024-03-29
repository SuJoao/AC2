// Ex3 b)

#include <detpic32.h>

int main(){

    TRISE = TRISE & 0xFFF0;

    char key;

    while(1){

        key = getChar();

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
            LATE = LATE | 0x000F;

            resetCoreTimer();
            while(readCoreTimer() < 20000000){
                key = inkey();
            }

            LATE = LATE & 0xFFF0;
        }
    }
    return 0;
}
