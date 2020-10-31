/*
 * File:   uart.c
 * Author: Matteo
 *
 * Created on October 31, 2020, 9:30 AM
 */

#include "xc.h"
//function to configure the SPI
void spi_config(int mode,int prm, int sec){
    SPI1CONbits.MSTEN = 1; // master mode
    SPI1CONbits.MODE16 = mode; // 8 bit mode
    SPI1CONbits.PPRE = prm; // primary prescaler
    SPI1CONbits.SPRE = sec; // secondary prescaler
    SPI1STATbits.SPIEN = 1; // enable SPI	
}

//Function to write a string of certain length to the LCD
void writeLCD(char *string,int length){
    int i=0; // index less than the length of the string 
    int j=0; // index between 0 and 15
    char a; //character to be written
    for(i=0;i<length;i++){ // for every character of the string 
        if(i==16){ // overflow condition to write in the second row if text is too long
            while(SPI1STATbits.SPITBF==1); // wait till buffer is available
            if(mode==1) // to switch between the two lines
                SPI1BUF=0xC0; // second line
            else
                SPI1BUF=0x80; // first line
	    while(SPI1STATbits.SPITBF==1); // wait till buffer is available
            SPI1BUF=string[i]; // write on the buffer
            a=string[i]; // debug porpuse
        }else if(string[i]=='\r' || string[i]=='\n'){ // If special character are written
		while(SPI1STATbits.SPITBF==1); // wait till buffer is available
		SPI1BUF=0x01 // clear the LCD display
		while(SPI1STATbits.SPITBF==1); // wait till buffer is available
		SPI1BUF=0x02 // restart from the first line
	}else{ // If no condition are activated
            while(SPI1STATbits.SPITBF==1); // wait till buffer is available
            SPI1BUF=string[i]; // write on the buffer
            a=string[i]; // debug porpuse
        }
    }
}
