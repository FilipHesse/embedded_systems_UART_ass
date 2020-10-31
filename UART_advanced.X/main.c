/*
 * File:   main.c
 * Author: filip,Matteo
 *
 * Created on October 30, 2020, 11:35 AM
 */


#include "xc.h"
#include <stdio.h>
#include "timer.h"
#include "button.h"
#include "uart.h"
#include "spi.h"

// define the counter for the elements received
    unsigned int counter = 0;

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
    tmr_wait_ms(TIMER1, 1000)
    
    //Setup SPI
    // TODO include SPI part
    spi_config(1,1,5)

    
    char c; // Character from UART
	char string1[16]; // first row
    char string2[16]; // second row
    int length=0;
 	int position=0
    
    // Main loop
    while (1) {
        // Read all the bytes, that have been stored to a ring buffer by the UART
        // Interrupt service routine into the variable c
        while ( ring_buffer_dequeue(getUARTRingBuffer(), &c) > 0){
            // Increase counter
           counter = counter + 1;
		   writeLCD(100+position,c,1);
		   position++;
		   if(c=='\n' || c=='\r' || position>16){
				position=0;
		   }
        }  // End of read from UART
	//Second row composition
	//Compute the string and its length
        length=sprintf(string,"Char Recv: %d\n",counter);
	//write string to the LCD
		writeLCD(200,string,length);

         //Button 5 pressed?
         if ( wasButtonS5Pressed() )
         {
             uart2TransmitIntAsStr(counter);
         }
        //Button 6 pressed?
		if ( wasButtonS6Pressed() )
        {
	     //Clear first row
             writeLCD('\r');
        }
        
        
        tmr_wait_period(TIMER2);
    }   // end of main loop

}
