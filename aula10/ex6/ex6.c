// Parte 2 ex1

#include <detpic32.h>

void putc1(char byte);

int main(){

    // Configure UART1 (115200,E,8,1)

    // Configure BaudRate Generator
    U1MODEbits.BRGH = 0;        // 16
    U1BRG = 10;                 // BRG ((20 000 000 / 16*115200) - 1)

    // Configure number of data bits, parity and number of stop bits
    U1MODEbits.PDSEL = 1;       // even parity bit
    U1MODEbits.STSEL = 0;       // 1 STOP bit

    // Enable the trasmitter and receiver modules
    U1STAbits.UTXEN = 1;        // trasmitter
    U1STAbits.URXEN = 1;        // receiver

    //Enable UART1
    U1MODEbits.ON = 1;

    while(1){

        putc1(0x5A);

        resetCoreTimer();
        while(readCoreTimer() < 200000);
    }

    return 0;
}


void putc1(char byte){

    while(U1STAbits.UTXBF == 1);
    U1TXREG = byte;

}


// 0xA5, 0xF0, 0x0F, 0xFF, 0x00)

