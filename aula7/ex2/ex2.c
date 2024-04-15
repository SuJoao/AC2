// Parte 1 Ex2

#include <detpic32.h>
#define N 8

void send2displays(unsigned char value);
unsigned char toBCD(unsigned char value);

volatile unsigned char voltage = 0;

int main(){

    // A/D config
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4= 0; 
    AD1CON1bits.SSRC = 7; 
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16; 
    AD1CON2bits.SMPI = N-1; 
    AD1CHSbits.CH0SA = 4; 
    AD1CON1bits.ON = 1;

    IPC6bits.AD1IP = 2;             // priority
    IFS1bits.AD1IF = 0;             // reset flag 
    IEC1bits.AD1IE = 1;             // enable

    // config display as output
    TRISB = TRISB & 0x80FF;
    // config select display as output
    TRISD = TRISD & 0xFF9F;

    unsigned int cnt = 0;

    EnableInterrupts();  

    while(1){

        if(cnt == 0){
            AD1CON1bits.ASAM = 1;
        }

        unsigned char bcd = toBCD(voltage);
        send2displays(bcd);

        cnt = (cnt + 1) % 20;

        resetCoreTimer();
        while(readCoreTimer() < 200000);
    }
    return 0;
}



void _int_(27) isr_adc(){
    
    int *p = (int*)(&ADC1BUF0);

    unsigned int sum = 0; 

    // 8 samples
    for(int i = 0; i < N; i++){
        sum += p[i*4];
    }

    unsigned int average = sum/N;
    unsigned int amplitude = (average*33+511)/1023;
    
    voltage = amplitude;

    IFS1bits.AD1IF = 0;
}


void send2displays(unsigned char value) {

    static const char disp7Scodes[] = { 0x3F, 0x06, 0x5B, 0x4F, 
                                        0x66, 0x6D, 0x7D, 0x07, 
                                        0x7F, 0x67, 0x77, 0x7C, 
                                        0x39, 0x5E, 0x79, 0x71 };

    static char displayFlag = 0;

    unsigned char display_low = value & 0x0F;
    unsigned char display_high = value >> 4;

    if (displayFlag == 0) {
        LATD = (LATD & 0xFF9F) | 0x0020;                         // RB6 = 0; RB5 = 1;     low active
        //LATB = (LATB & 0x80FF) | (disp7Scodes[value & 0x0F] << 8);
        LATB = (LATB & 0x80FF) | (disp7Scodes[display_low] << 8);
    } else {
        LATD = (LATD & 0xFF9F) | 0x0040;                         // RB6 = 1; RB5 = 0;     high active
        //LATB = (LATB & 0x80FF) | (disp7Scodes[value >> 4] << 8);
        LATB = (LATB & 0x80FF) | (disp7Scodes[display_high] << 8);
    }
    displayFlag = displayFlag ^ 1;
}


unsigned char toBCD(unsigned char value) {

    return ((value / 10) << 4) + (value % 10);
}
