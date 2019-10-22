#ifndef UART_H
#define UART_H

char initUART(unsigned long int baudrate);
char UART_TX_Empty(void);
char UART_Data_Ready(void);
char readUART(void);         
void readString(char *Output, unsigned int length);
void writeUART(char data);  
void writeString (char *text);


#endif