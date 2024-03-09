// PARTE I Ex1

#include <detpic32.h>
#define K 2000

void delay(unsigned int ms);

int main(){

    //TRISCbits.TRISC14 = 0;
    TRISC = TRISC & 0xBFFF;
    
    while(1){

        delay(500);

        //LATCbits.LATC14 = !LATCbits.LATC14;
        LATC = LATC ^ 0x4000;
    }


    return 0;
}

void delay(unsigned int ms){

    resetCoreTimer();

    while(readCoreTimer() < K*ms);

}
