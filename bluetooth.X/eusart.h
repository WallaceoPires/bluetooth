#ifndef EUSART_H
#define EUSART_H

unsigned char statusRxEUSART( void );
unsigned char readEUSART( void );
unsigned char errorRxEUSART( void );
void resetErrorRxEUSART( void );
void writeEUSART( unsigned char d );    // escreve caracter
unsigned char statusTxEUSART( void );
void writeString( const char * str );     // escreve frase no vetor apontado
void initEUSART( unsigned long int baudRate );
void interrupt_EUSART_RX( void );

#endif
