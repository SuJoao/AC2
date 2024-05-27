#include <detpic32.h>

#define DisableUart2RxInterrupt()   IEC1bits.U2RXIE = 0
#define EnableUart2RxInterrupt()    IEC1bits.U2RXIE = 1
#define DisableUart2TxInterrupt()   IEC1bits.U2TXIE = 0
#define EnableUart2TxInterrupt()    IEC1bits.U2TXIE = 1

#define TRUE 1
#define FALSE 0

#define BUF_SIZE 8
#define INDEX_MASK (BUF_SIZE-1)

typedef struct{
    unsigned char data[BUF_SIZE];
    unsigned int head;          // read
    unsigned int tail;          // write
    unsigned int count;         // total of characters

} circularBuffer;


volatile circularBuffer txb; // Transmission buffer
volatile circularBuffer rxb; // Reception buffer

// Initialize variables
void comDrv_flushRx(void);
void comDrv_flushTx(void);

// send characters (putChar())
void comDrv_putc(char ch);
void comDrv_puts(char *s);

// read characters (readChar())
char comDrv_getc(char *pchar);


int main(){

    // Configure BaudRate Generator (115200,'N',1)
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

    // config TX and RX interrupts
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;

    IFS1bits.U2RXIF = 0;
    IFS1bits.U2TXIF = 0;

    U2STAbits.URXISEL = 0;
    U2STAbits.UTXISEL = 0;

    IPC8bits.U2IP = 1;

    comDrv_flushRx();
    comDrv_flushTx();

    unsigned char c;

    EnableInterrupts();


    comDrv_puts("Teste do bloco de transmissao do device driver!...\n");
    comDrv_puts("PIC32 UART Device-driver\n");
    
    while(1){
        
        // c = getChar();  (bloqueante)
        //while(comDrv_getc(&c) == FALSE);
        //comDrv_putc(c);

        // c = inkey() (não bloqueante)
        if(comDrv_getc(&c)){
            comDrv_putc(c);
        }

    }

    return 0;
}


void comDrv_flushRx(void){
    rxb.count = 0;
    rxb.tail = 0;
    rxb.head = 0;
}

void comDrv_flushTx(void){
    txb.count = 0;
    txb.tail = 0;
    txb.head = 0;
}


// transmission

void comDrv_putc(char ch){
    while(txb.count == BUF_SIZE);

    txb.data[txb.tail] = ch;

    txb.tail = (txb.tail + 1) & INDEX_MASK;

    DisableUart2TxInterrupt();
    txb.count++;
    EnableUart2TxInterrupt();
}


void comDrv_puts(char *s){
    
    unsigned int i = 0;
    while(s[i] != '\0'){
        comDrv_putc(s[i]);
        i++;
    }
}



// reception

char comDrv_getc(char *pchar){

    if(rxb.count == 0) return FALSE;

    DisableUart2RxInterrupt();

    *pchar = rxb.data[rxb.head];

    rxb.count--;
    rxb.head = (rxb.head + 1) & INDEX_MASK;

    EnableUart2RxInterrupt(); 

    return TRUE;
}


void _int_(32) isr_uart2(void){

    // transmission RSI, write character to the transmission FIFO
    if(IFS1bits.U2TXIF == 1){
        if(txb.count > 0){
            U2TXREG = txb.data[txb.head];
            txb.head = (txb.head + 1) & INDEX_MASK;
            txb.count--;
        }
        if(txb.count == 0){
            DisableUart2TxInterrupt();
        }
        
        IFS1bits.U2TXIF = 0;
    }

    // reception RSI, write character to the device driver's reception circular buffer 
    if(IFS1bits.U2RXIF == 1){
        rxb.data[rxb.tail] = U2RXREG;
        rxb.tail = (rxb.tail + 1) & INDEX_MASK;
     
        // if the buffer is not full, increment count
        if(rxb.count < BUF_SIZE){
            rxb.count++;
        
        //if the buffer is full, discard oldest character (count do not change)
        }else{
            rxb.head = (rxb.head + 1) & INDEX_MASK; 
        }

        IFS1bits.U2RXIF = 0;
    }
}
