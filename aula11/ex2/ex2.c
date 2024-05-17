// Parte 1 ex1

#include <detpic32.h>

void putc(char byte);
void putstr(char *str);
void putstrInt(char *s);



typedef struct{
    char mem[100];  // Storage area
    int nchar;      // Number of characters to be transmitted
    int posrd;      // Position of the next character to be transmitted
} t_buf;

volatile t_buf txbuf;

int main(){

    // Configure UART2: 115200, N, 8, 1
    // 600, N, 8, 1

    // Configure BaudRate Generator
    U2MODEbits.BRGH = 0;        // /16
    U2BRG = 2082;               // BRG ((20 000 000 / 16*600) - 1)

    // Configure number of data bits, parity and number of stop bits
    U2MODEbits.PDSEL = 0;       // 0 parity bit
    U2MODEbits.STSEL = 0;       // 1 STOP bit

    // Enable the trasmitter and receiver modules
    U2STAbits.UTXEN = 1;        // trasmitter
    U2STAbits.URXEN = 1;        // receiver

    //Enable UART2
    U2MODEbits.ON = 1;


    // config int

    //IEC1bits.U2RXIE = 0;
    IEC1bits.U2TXIE = 0;

    IPC8bits.U2IP = 1;

    //IFS1bits.U2RXIF = 0;
    IFS1bits.U2TXIF = 0;

    //U2STAbits.URXISEL = 0;
    U2STAbits.UTXISEL = 0;

    EnableInterrupts();


    txbuf.nchar = 0;

    while(1){

        putstrInt("Test string which can be as long as you like, up to a maximum of 100 characters\n");
    }

    return 0;
}


void putstrInt(char *s){

    while(txbuf.nchar > 0);

    unsigned int i = 0;
    while(s[i] != '\0'){
        txbuf.mem[i] = s[i];
        i++;
        txbuf.nchar++;
    }

    txbuf.posrd = 0;

    IEC1bits.U2TXIE = 1;
}

void _int_(32) isr_uart2(void){
    
    if(IFS1bits.U2TXIF == 1){
        
        if(txbuf.nchar > 0){
            U2TXREG = txbuf.mem[txbuf.posrd];
            txbuf.posrd++;
            txbuf.nchar--;
        }else{
            IEC1bits.U2TXIE = 0;
        }

        IFS1bits.U2TXIF = 0;
    }
}
