// PARTE 2       Ex 1)

#include <detpic32.h> 
#define K 20000


// 10hz = 2 000 000
// 5hz = 4 000 000
// 1hz = 20 000 000


void delay(int ms);

int main(){

    int cnt1 = 0;
    int cnt5 = 0;
    int cnt10 = 0;

    while(1){

        putChar('\r');
        printInt(cnt1, 10 | 5 << 16);

        putChar('\t');
        printInt(cnt5, 10 | 5 << 16);

        putChar('\t');
        printInt(cnt10, 10 | 5 << 16);


        delay(100); // 100ms = 0,1s = 10hz
        cnt10++;

        if(cnt10 % 2 == 0) cnt5++;

        if(cnt10 % 10 == 0) cnt1++;

    }

    return 0;
}


void delay(int ms){
    
    resetCoreTimer();
    while(readCoreTimer() < K * ms);

}
