// Parte 1 ex7

#include <detpic32.h>

void putc(char byte);

int main(){

    // Configure UART2 (115200, N, 8, 1)

    // Configure BaudRate Generator
    U2MODEbits.BRGH = 0;        // 16
    U2BRG = 10;                 // BRG ((20 000 000 / 16*115200) - 1)

    // Configure number of data bits, parity and number of stop bits
    U2MODEbits.PDSEL = 0;       // 0 parity bit
    U2MODEbits.STSEL = 0;       // 1 STOP bit

    // Enable the trasmitter and receiver modules
    U2STAbits.UTXEN = 1;        // trasmitter
    U2STAbits.URXEN = 1;        // receiver

    //Enable UART2
    U2MODEbits.ON = 1;

    unsigned int count = 0;

    while(1){

        unsigned int newCount = count;

        for(int i = 0; i < 4; i++){
            unsigned int bit = newCount & 0x0008;
            if(bit != 0){
                putc('1');
            }else{
                putc('0');
            }
            newCount = newCount << 1;
        }
        count = (count + 1) % 10;
        putc('\n');

        resetCoreTimer();
        while(readCoreTimer() < 4000000);       // 5hz

    }

    return 0;
}


void putc(char byte){

    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;

}
