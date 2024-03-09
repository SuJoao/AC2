// PARTE I Ex3

#include <detpic32.h>

int main(){

    TRISE = TRISE & 0xFF87;

    int count = 0;

    while(1){

        LATE = (LATE & 0xFF87) | count << 3;

        resetCoreTimer();
        while(readCoreTimer() < 7407407);

        //count = count > 0 ? count - 1 : 9;
        count = (count + 9) % 10;
    }

    return 0;
}
