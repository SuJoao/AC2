// Ex 5 a)

#include <detpic32.h>

int main(){

    int counter = 0;

    while(1){

        printInt(counter, 10 | 2 << 16);
        putChar('\r');
        
        resetCoreTimer();
        while(readCoreTimer() < 2000000);           // 10hz

        counter = (counter + 1) % 100;
        
    }

    return 0;
}
