// Parte 1 ex4,5

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

    while(1){

        putstr("String de teste\n");

        resetCoreTimer();
        while(readCoreTimer() < 20000000);

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


// Configure UART2 (600,N,8,1)

//U2MODEbits.BRGH = 0;        // 16
//U2BRG = 2082;               // BRG ((20000000 / (16*600)) - 1)

//U2MODEbits.PDSEL = 0;       // none parity bit
//U2MODEbits.STSEL = 0;       // 1 STOP bit



// Configure UART2 (1200,O,8,2)

//U2MODEbits.BRGH = 0;        // 16
//U2BRG = 1041;               // BRG ((20 000 000 / (16*1200)) - 1)

//U2MODEbits.PDSEL = 2;       // odd parity bit
//U2MODEbits.STSEL = 1;       // 2 STOP bit


// Configure UART2 (9600,E,8,1)

//U2MODEbits.BRGH = 0;        // 16
//U2BRG = 129;                // BRG ((20 000 000 / (16*9600)) - 1)

//U2MODEbits.PDSEL = 1;       // even parity bit
//U2MODEbits.STSEL = 0;       // 1 STOP bit


// Configure UART2 (19200,N,8,2)

//U2MODEbits.BRGH = 0;        // 16
//U2BRG = 64;                 // BRG ((20 000 000 / (16*19200)) - 1)

//U2MODEbits.PDSEL = 0;       // none parity bit
//U2MODEbits.STSEL = 1;       // 2 STOP bit


// Configure UART2 (115200,E,8,1)

//U2MODEbits.BRGH = 0;        // 16
//U2BRG = 10;                 // BRG ((20 000 000 / (16*115200)) - 1)

//U2MODEbits.PDSEL = 1;       // even parity bit
//U2MODEbits.STSEL = 0;       // 1 STOP bit


// Configure UART2 (230400,E,8,2)

//U2MODEbits.BRGH = 1;        // 4
//U2BRG = 21;                 // BRG ((20 000 000 / (4*230400)) - 1)

//U2MODEbits.PDSEL = 1;       // even parity bit
//U2MODEbits.STSEL = 1;       // 1 STOP bit


// Configure UART2 (460800,O,8,1)

//U2MODEbits.BRGH = 1;        // 4
//U2BRG = 10;                 // BRG ((20 000 000 / (4*460800)) - 1)

//U2MODEbits.PDSEL = 2;       // even parity bit
//U2MODEbits.STSEL = 0;       // 1 STOP bit


// Configure UART2 (576000,N,8,1)

//U2MODEbits.BRGH = 1;        // 4
//U2BRG = 8;                 // BRG ((20 000 000 / (4*576000)) - 1)

//U2MODEbits.PDSEL = 0;       // even parity bit
//U2MODEbits.STSEL = 0;       // 1 STOP bit
