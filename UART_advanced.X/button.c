/*
 * File:   button.c
 * Author: filip
 *
 * Created on October 30, 2020, 9:08 PM
 */


#include "xc.h"
#include "button.h"
#include "timer.h"

int buttonS5Pressed;

//Interrupt Service Routine for input flag
void __attribute__((__interrupt__, __auto_psv__)) _INT0Interrupt(){
    // reset interrupt flag
    IFS0bits.INT0IF = 0;
    
    // set flag, that button has been pressed
    buttonS5Pressed = true;
    
    tmr_setup_period(TIMER3,100);
    IEC0bits.INT0IE = 0;    //Disable interrupt for timer period to avoid 
                            //bouncing effects
    IEC0bits.T3IE = 1;      //Enable timer 3 interrupt  
}

//Interrupt Service Routine for timer
void __attribute__((__interrupt__, __auto_psv__)) _T3Interrupt(){
    
    T2CONbits.TON = 0;      //Stop timer
    IFS0bits.T3IF = 0;      //Reset interrupt flag of timer 3
      
    IFS0bits.INT0IF = 0;    //Reset interrupt flag of INT0 AGAIN, because in the
                            //meantime, when the timer was running, the flag 
                            //could have been set to high again
    IEC0bits.INT0IE = 1;    //Disable interrupt for timer period to avoid 
                            //bouncing effects

}

void setupButtonS5()
{
    // Button S5 is connected to Pin E8,which is shared with INT0,
    // which we will use to raise interrupts
    IEC0bits.INT0IE = 1;        //Enable interrupt
    buttonS5Pressed = false;    //Initialize flag to 0
}


// Automatically resets the buttonPressed flag to false, if it was true
bool wasButtonS5Pressed()
{
    if ( buttonS5Pressed )
    {
        buttonS5Pressed = false;
        return true;
    }
    else
    {
        return false;
    }
}
        
