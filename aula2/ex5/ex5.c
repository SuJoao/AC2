// PARTE 2       Ex 4)

#include <detpic32.h> 
#define K 20000


// 10hz = 2 000 000
// 5hz = 4 000 000
// 1hz = 20 000 000


// 20hz = 1 000 000
// 10hz = 2 000 000
// 2hz = 10 000 000

void delay(int ms);

int main(){

    int cnt1 = 0;
    int cnt5 = 0;
    int cnt10 = 0;

    char key;
    int ms = 100;

    while(1){

        key = inkey();
        if(key == 'n') ms = 100;

        if(key == 'a') ms = 50;
        
        if(key == 's'){
            while(key  != 'r'){
                key = getChar();
            }
        }
        
        if(key == 'r') key = inkey();

        putChar('\r');
        printInt(cnt1, 10 | 5 << 16);

        putChar('\t');
        printInt(cnt5, 10 | 5 << 16);

        putChar('\t');
        printInt(cnt10, 10 | 5 << 16);

        delay(ms);
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

