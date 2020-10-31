/*
 * File:   main.c
 * Author: filip
 *
 * Created on October 30, 2020, 11:35 AM
 */


#include "xc.h"
#include <stdio.h>
#include "timer.h"
#include "button.h"
#include "uart.h"



int main(void) {

    // Setup timer for main loop, I define loop frequency of 100 Hz (10 ms)
    tmr_setup_period(TIMER2, 10);
    
    //Setup UART
    uart_config(1, 9600);
    uart_config(2, 9600);
    
    //Setup Button S5
    setupButtonS5();
    
    //Wait for display to come up, use timer function from second assignment 
    //TODO include time functions!
    //    tmr_wait_ms(TIMER1, 1000)
    
    //Setup SPI
    // TODO include SPI part
    // spi_config()

    // define the counter for the elements received
    unsigned int counter = 0;
    char c; // Character from UART
    
    // Main loop
    while (1) {
        // Read all the bytes, that have been stored to a ring buffer by the UART
        // Interrupt service routine into the variable c
        while ( ring_buffer_dequeue(getUARTRingBuffer(), &c) > 0){
            // Increase counter
           counter = counter + 1;

           // Check if received character equals CR or LF
           // if ( c  == CR,LF  )
           // {
               // put character to SPI--
               // spi_put_char(c);
               //Refine the above sending to spi, s.t. restart writing from beginning when line is full
           // else
           //{
           //  SPI clear first row
           //}
           //
        //}  
        }  // End of read from UART
        
         //Button 5 pressed?
         if ( wasButtonS5Pressed() )
        {
             uart2TransmitIntAsStr(counter);
        }
        //Button 6 pressed?
	if ( wasButtonS6Pressed() )
        {
	     //Clear first row
             uart2TransmitIntAsStr(counter);
        }
        
        
        tmr_wait_period(TIMER1);
    }   // end of main loop

}
