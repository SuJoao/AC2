// Parte 1 ex1

#include <detpic32.h>

void putc(char byte);
void putstr(char *str);

int main(){

    // Configure UART2: 115200, N, 8, 1

    // Configure BaudRate Generator
    U2MODEbits.BRGH = 0;        // /16
    U2BRG = 10;                 // BRG ((20 000 000 / 16*115200) - 1)

    // Configure number of data bits, parity and number of stop bits
    U2MODEbits.PDSEL = 0;       // 0 parity bit
    U2MODEbits.STSEL = 0;       // 1 STOP bit

    // Enable the trasmitter and receiver modules
    U2STAbits.UTXEN = 1;        // trasmitter
    U2STAbits.URXEN = 1;        // receiver

    //Enable UART2
    U2MODEbits.ON = 1;


    // config int

    IEC1bits.U2RXIE = 1;
    //IEC1bits.U2TXIE = 0;

    IPC8bits.U2IP = 1;

    IFS1bits.U2RXIF = 0;
    //IFS1bits.U2TXIF = 0;

    U2STAbits.URXISEL = 0;
    //U2STAbits.UTXISEL = 0;

    EnableInterrupts();

    TRISC = TRISC & 0xBFFF;
    LATC = LATC & 0xBFFF;

    while(1);

    return 0;
}


void _int_(32) isr_uart2(void){

    if(IFS1bits.U2RXIF == 1){

        unsigned char c = U2RXREG;  

        if(c == '?'){
            putstr("AC2-Guiao 11");
        }else if(c == 'T'){
            LATC = LATC | 0x4000;
            putc(c);
        }else if(c == 't'){
            LATC = LATC & 0xBFFF;
            putc(c);
        }else{
            putc(c);
        }

        IFS1bits.U2RXIF = 0;
    }
}

void putc(char byte){

    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

void putstr(char *str){ 

    unsigned int count = 0;

    while(str[count] != '\0'){
        putc(str[count]);
        count++;
    }
}
