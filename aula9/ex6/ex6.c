// Adicional 2

#include <detpic32.h>

#define N 8

volatile int voltage = 0;

void send2displays(unsigned char value);
unsigned char toBCD(unsigned char value);
void setPWM(unsigned int dutyCycle);

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

    // A/D interrupt
    IPC6bits.AD1IP = 3;           
    IFS1bits.AD1IF = 0;        
    IEC1bits.AD1IE = 1;          


    // Display config
    TRISB = TRISB & 0x80FF;
    TRISD = TRISD & 0xFF9F;

    // config sw1 and sw2 (RB0 and RB1) as input
    TRISB = TRISB | 0x0003;

    // config LED11 (RC14) as output
    TRISC = TRISC & 0xBFFF;

    // T3 config (100hz)
    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T3CONbits.TON = 1;

    // T3 interrupt
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;


    // T1 config (5hz)
    T1CONbits.TCKPS = 2;
    PR1 = 62499;
    TMR1 = 0;
    T1CONbits.TON = 1;

    // T1 interrupt
    IPC1bits.T1IP = 1;
    IEC0bits.T1IE = 0;
    IFS0bits.T1IF = 0;

    // OC1 config 
    OC1CONbits.OCM = 6; 
    OC1CONbits.OCTSEL = 1;
    OC1RS = 125;
    OC1CONbits.ON = 1;

    EnableInterrupts();

    unsigned int key;
    unsigned int dutyCycle;

    while(1){

        key = PORTB & 0x0003;

        if(key == 0){
            IEC0bits.T1IE = 1;
            setPWM(0);

        }else if(key == 1){
            IEC0bits.T1IE = 0;
            setPWM(100);

        }else{
            IEC0bits.T1IE = 1;
            dutyCycle = voltage * 3;
            setPWM(dutyCycle);
        }

        LATC = (LATC & 0xBFFF) | ((PORTD & 0x0001) << 14); 
    }
    return 0;
}


void _int_(27) isr_adc(){

    int *p = (int*)(&ADC1BUF0);
    unsigned int sum = 0;
    for (int i = 0; i < N; i++){
        sum += p[i*4];
    }

    unsigned int average = sum/N;    
    voltage = (average * 33 + 511) / 1023;

    IFS1bits.AD1IF = 0; 
}


void _int_(12) isr_T3(void){

    // send to display
    unsigned char bcd = toBCD(voltage);
    send2displays(bcd);

    IFS0bits.T3IF = 0;
}

void _int_(4) isr_T1(void){

    // start A/D conversion
    AD1CON1bits.ASAM = 1;

    IFS0bits.T1IF = 0;
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
        LATB = (LATB & 0x80FF) | (disp7Scodes[display_low] << 8);
    } else {
        LATD = (LATD & 0xFF9F) | 0x0040;                         // RB6 = 1; RB5 = 0;     high active
        LATB = (LATB & 0x80FF) | (disp7Scodes[display_high] << 8);
    }
    displayFlag = displayFlag ^ 1;
}


unsigned char toBCD(unsigned char value) {

    return ((value / 10) << 4) + (value % 10);
}

void setPWM(unsigned int dutyCycle){

    OC1RS = (49999 * dutyCycle) / 100;
}
