// Ex7 a)

#include <detpic32.h>

int main(){

    // sw as input
    TRISB = TRISB | 0x000F;

    while(1){

        printStr("DS=");
        putChar(((PORTB & 0x0008) >> 3) + '0');
        putChar(((PORTB & 0x0004) >> 2) + '0');
        putChar(((PORTB & 0x0002) >> 1) + '0');
        putChar((PORTB & 0x0001) + '0');
        putChar('\r');

        resetCoreTimer();
        while(readCoreTimer() < 20000000);
    }

    return 0;
}
