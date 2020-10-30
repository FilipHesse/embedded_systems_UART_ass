/*
 * File:   main.c
 * Author: filip
 *
 * Created on October 30, 2020, 11:35 AM
 */


#include "xc.h"
#include <stdio.h>

void uart_config()
{
    U2BRG = 11;
    U2MODEbits.UARTEN = 1;
    U2STAbits.UTXEN = 1;
}

int main(void) {

//Wait for display to come up, use timer function from second assignment 
// TODO include time functions!
//    tmr_wait_ms(TIMER1, 1000)
    
//Setup SPI
// TODO include SPI part
// spi_config()
    
    //Setup UART
    uart_config();
    
    // define the counter for the elements received
    int counter = 0
    while (1) {
        // Adjust the line below to: is there something in the variable received_bytes_buffer
        if (U2STABITS.URXDA == 1)
        // Process received bytes
        {
            // iterate over buffer
            //for (...)
            //{
                       // Increase counter
                      //  counter = counter + 1;
            
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
            
            

            
            //Button 5 pressed? Use interrupt version! Video Interrupt exercises: 8:00 ...
            
                //Send counter number to UART
            
            //Button 6 pressed?
            
            //Clear first row
            
            
        }
    }

}
