/*
 * File:   uart.c
 * Author: filip
 *
 * Created on October 30, 2020, 11:00 PM
 */
#include "xc.h"
#include "uart.h"

#define QUEUE_SIZE 32
#include "ringbuffer.h"

queue_t input_queue;

//Interrupt Service Routine for Receiving from UART1
void __attribute__((__interrupt__, __auto_psv__)) _U1RXInterrupt(){
    // reset interrupt flag
    IFS0bits.U1RXIF = 0;
    
    //read char
    char c = U1RXREG;
    
    // push char into FIFO queue
    queue_write(&input_queue, (void*)(c));
}


void uart_config(int uartNumber, int baudRate)
{
    if (uartNumber == 1)
    {
        input_queue = {0, 0, QUEUE_SIZE, malloc(sizeof(void*) * QUEUE_SIZE)};
        
        U1BRG = (7372800 / 4) / (16 * baudRate) - 1;
        U1MODEbits.UARTEN = 1;  //Enable UART1
        U1STAbits.UTXEN = 1;
        
        IEC0bits.U1RXIE = 1;    //Enable UART interrupts for receiving
        U1STAbits.URXISEL = 0;  //Interrupt is set, when a character is received
                                // We immediately queue the contents in our 
                                //internal buffer
    }
    
    if (uartNumber == 2)
    {
        U2BRG = (7372800 / 4) / (16 * baudRate) - 1;
        U2MODEbits.UARTEN = 1;
        U2STAbits.UTXEN = 1;
    }
}

void* uart1_read_value()
{
    return queue_read(&input_queue);
}
