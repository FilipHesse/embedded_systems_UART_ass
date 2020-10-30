/*
 * File:   uart.c
 * Author: filip
 *
 * Created on October 30, 2020, 11:00 PM
 */
#include "xc.h"
#include "uart.h"

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
