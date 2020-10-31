// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SPI_H
#define	SPI_H
// Funtion to configure the spi (LCD)
void spi_config(int mode,int prm, int sec);
// Function to write on the LCD
void writeLCD(char *string,int length);

#endif	/* XC_HEADER_TEMPLATE_H */
