// Parte 1 ex2, ex3

#include <detpic32.h>

void putc(char byte);

// Configure UART2 (115200, N, 8, 1)

int main(){

    // Configure BaudRate Generator
    U2MODEbits.BRGH = 1;        // 0 : /16 or 1 : /4
    U2BRG = 42;                 // BRG /16 = ((20 000 000 / 16*115200) - 1) or /4 = ((20 000 000 / 4*115200) - 1)  

    // Configure number of data bits, parity and number of stop bits
    U2MODEbits.PDSEL = 0;       // 0 parity bit
    U2MODEbits.STSEL = 0;       // 1 STOP bit

    // Enable the trasmitter and receiver modules
    U2STAbits.UTXEN = 1;        // trasmitter
    U2STAbits.URXEN = 1;        // receiver

    //Enable UART2
    U2MODEbits.ON = 1;

    while(1){

        putc('+');

        // wait 1s
        resetCoreTimer();
        while(readCoreTimer() < 20000000);        

    }

    return 0;
}


void putc(char byte){

    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;

}
