// Parte 1 ex6

#include <detpic32.h>

void putc(char byte);
char getc(void);

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

    while(1){

        char c = getc();
        putc(c);

    }

    return 0;
}


void putc(char byte){

    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;

}


char getc(void){

    while(U2STAbits.URXDA == 0);
    return U2RXREG;

}
