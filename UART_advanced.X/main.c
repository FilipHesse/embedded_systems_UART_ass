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

void uart_config(int uartNumber, int baudRate)
{
    if (uartNumber == 1)
    {
        U1BRG = (7372800 / 4) / (16 * baudRate) - 1;
        U1MODEbits.UARTEN = 1;
        U1STAbits.UTXEN = 1;
    }
    
    if (uartNumber == 2)
    {
        U2BRG = (7372800 / 4) / (16 * baudRate) - 1;
        U2MODEbits.UARTEN = 1;
        U2STAbits.UTXEN = 1;
    }
}

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
    char c;
    while (1) {
        // Adjust the line below to: is there something in the variable received_bytes_buffer
        if (U1STAbits.URXDA == 1)
        // Process received bytes
        {
            c = U1RXREG;
            
            // iterate over buffer
            //for (...)
            //{
                       // Increase counter
                      counter = counter + 1;
            
                            // Check if received character equals CR or LF
                      // if ( U2RXREG (/item) == CR,LF  )
                      // {
                          // put character to SPI--
                          // spi_put_char(U2RXREG);
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
            // Convert counter number to string
            char counterStr[10] = "";
            sprintf(counterStr, "%u", counter);

            // iterate over the characters of the string and send all of them
            int i = 0;
            while(counterStr[i] != '\0')
            {
                //Send counter number to UART
                U2TXREG = counterStr[i];
                i=i+1;
            }
        }
        //Button 6 pressed?

        //Clear first row
        
        tmr_wait_period(TIMER1);
    }   // end of main loop

}
