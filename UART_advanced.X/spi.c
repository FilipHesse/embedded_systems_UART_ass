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
void writeLCD(int row,char *string,int length){
    int i=0; // index less than the length of the string 
    int j=0; // index between 0 and 15
	int position=0;
    char a; //character to be written
	if(row/100==1){
		while(SPI1STATbits.SPITBF==1); // wait till buffer is available
		position=0x80+row%100;
		SPI1BUF=position; // write on the first line
    }
	else{
		while(SPI1STATbits.SPITBF==1); // wait till buffer is available
		position=0xC0+row%200;
		SPI1BUF=0xC0; // write on the second line
	}

    if(length<16){

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
