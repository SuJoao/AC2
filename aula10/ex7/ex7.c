// Parte 3 ex1, 2, 3

#include <detpic32.h>

void putstr(char *str);
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

    // config RD11 as output
    TRISD = TRISD & 0xF7FF;
    LATD = LATD & 0xF7FF;

    while(1){

        while(U2STAbits.TRMT == 0);

        LATD = LATD | 0x0800;

        putstr("12345");

        LATD = LATD & 0xF7FF;
    }

    return 0;
}


void putstr(char *str){ 

    unsigned int count = 0;

    while(str[count] != '\0'){
        putc(str[count]);
        count++;
    }
}


void putc(char byte){

    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

//1)
// "123456789", "123456789A", "123456789AB"

//2)
// 19200 bps
// (20000000 / (19200 * 16)) -1
