#include "p24fj64ga002.h"
#include "timer.h"

#define FCY 14745600.0
#define PRESCALAR 256.0
#define ONE_SECOND FCY/PRESCALAR -1


void initTimer1(){
    PR1 = ONE_SECOND/2.0;
    TMR1 = 0;
    T1CONbits.TCKPS = 0b11;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    T1CONbits.TON = 1;


}

void initTimer2(){
    IFS0bits.T2IF = 0;
    T2CONbits.TCKPS = 0;
}

void delayUs(unsigned int delay){
    IFS0bits.T2IF = 0;
    T2CONbits.TCKPS = 0;
    TMR2 = 0x0000;
    PR2 = 14*delay;
    T2CONbits.TON = 1;
    while(IFS0bits.T2IF == 0){
        if(TMR2 > PR2) break;
    }
    T2CONbits.TON = 0;
}

void initTimer3(){
    PR3 = ONE_SECOND;
    TMR3 = 0;
    T3CONbits.TCKPS = 0b11;
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 1;
    T3CONbits.TON = 1;

}