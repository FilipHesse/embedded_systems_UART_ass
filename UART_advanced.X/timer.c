/*
 * File:   timer.c
 * Author: filip
 *
 * Created on October 30, 2020, 8:42 PM
 */


#include "xc.h"

#include "timer.h"

void tmr_setup_period(int timer, int ms){
    TMR1 = 0; // reset timer counter
    // Fcy = 1843200 (number of clocks in one second)
    // this is too high to be put in a 16 bit register (max 65535)
    // If we set a prescaler of 1:8 we have 1843200/8 = 230400 still too high!
    // If we set a prescaler of 1:64 we have 1843200/64 = 28800 nr of counts in 1 sec -> GOOD!
    
    //We want to blink with a period of ms(param)/1000ms 
    float rate_in_sec =(float)ms/1000.0;
    PR1 = 28800*rate_in_sec;
    T1CONbits.TCKPS = 2; // prescaler 1:64
    T1CONbits.TCS = 0; // use internal clock
    T1CONbits.TON = 1; // starts the timer!
}


void tmr_wait_period(int timer)
{
    int i = 0;
    
    // Don't do anything as long as the Timer interrupt flag is not set
    switch(timer){
        case TIMER1: 
        {
            i=0;

            while(IFS0bits.T1IF == 0) 
            {
                i = i+1;
            }
            IFS0bits.T1IF = 0; 
            TMR1 = 0; // reset timer counter
            break;
        }   
        case TIMER2:             
        {
            i=0;
            while(IFS0bits.T2IF == 0) 
            {
                i = i+1;
            }
            IFS0bits.T2IF = 0; 
            TMR2 = 0; // reset timer counter
            break;
        }
    }
}
