/*
 * File:   uart.c
 * Author: Matteo
 *
 * Created on October 31, 2020, 9:30 AM
 */

#include "xc.h"
//function to configure the SPI
void spi_config(int mode,int prm, int sec){
/* Parameters:
	mode: which set the mode on Master(1) or Slave(0)
	prm: primary prescaler
	sec: secondary prescaler
*/
    SPI1CONbits.MSTEN = 1; // master mode
    SPI1CONbits.MODE16 = mode; // 8 bit mode
    SPI1CONbits.PPRE = prm; // primary prescaler
    SPI1CONbits.SPRE = sec; // secondary prescaler
    SPI1STATbits.SPIEN = 1; // enable SPI	
}

//Function to write a string of certain length to the LCD
void writeLCD(int row,char *string,int length){
/* Parameters:
	row:position from 0 to 31 in which [0 15] represent the first row indeces and [16 31] represent the second row indeces
	string: represent the character array to be sent to the LCD
	length: represent the length of the string array
*/
    int i=0; // index less than the length of the string 
    char a; //character to be written
	if(row<16){ // first row indeces are less than 16
		while(SPI1STATbits.SPITBF==1); // wait till buffer is available
		SPI1BUF=0x80+row; // write on the first line
    }
	else{ // you are writing in the second row
		while(SPI1STATbits.SPITBF==1); // wait till buffer is available
		SPI1BUF=0xC0+row; // write on the second line
	}

    // Write only if the length is less than the LCD width
    if(row%16+length<16){

	    for(i=0;i<length;i++){ // for every character of the string 
    		if(string[i]=='\r' || string[i]=='\n'){ // If special character are written
        		while(SPI1STATbits.SPITBF==1); // wait till buffer is available
        		SPI1BUF=0x01; // clear the LCD display
        		while(SPI1STATbits.SPITBF==1); // wait till buffer is available
        		SPI1BUF=0x02; // restart from the first line
            }
            else{ // If no condition are activated
           		while(SPI1STATbits.SPITBF==1); // wait till buffer is available
				SPI1BUF=string[i]; // write on the buffer
				a=string[i]; // debug porpuse
            }
		}
    }
}

