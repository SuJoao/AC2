// Ex 5 b)

#include <detpic32.h>

int main(){

    unsigned int counter = 0;
    unsigned freq = 10;
    unsigned int cycles = 2000000;
    unsigned char key;
    
    while(1){

        key = inkey();

        if(key == '0'){
            freq = 2 * (1 + 0);
            cycles = 10000000;

        }else if(key == '1'){
            freq = 2 * (1 + 1);
            cycles = 5000000;

        }else if(key == '2'){
            freq = 2 * (1 + 2);
            cycles = 3333333;
            
        }else if(key == '3'){
            freq = 2 * (1 + 3);
            cycles = 2500000;

        }else if (key == '4'){
            freq = 2 * (1 + 4);
            cycles = 2000000;

        }else if(key == '\n'){
            printInt(counter, 10 | 2 << 16);
            printStr(", ");
            printInt(freq, 10 | 1 << 16);
            printStr(" Hz \r");

            //printf(", %.2d Hz \r", freq);
        
        } else{
            printInt(counter, 10 | 2 << 16);
            putChar('\r');
        }
 
        resetCoreTimer();
        while(readCoreTimer() < cycles);

        counter = (counter + 1) % 100;
        
    }

    return 0;
}
