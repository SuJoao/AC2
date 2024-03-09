// PARTE I Ex2

#include <detpic32.h>

int main(){

    TRISE = TRISE & 0xFF87;

    int count = 0;

    while(1){

        LATE = (LATE & 0xFF87) | count << 3;

        resetCoreTimer();
        while(readCoreTimer() < 4347826);

        count = (count + 1) % 10;

    }

    return 0;
}
