
#ifndef SERIAL_H
#define	SERIAL_H

#define dout    PORTBbits.RB0
#define din     PORTBbits.RB1
#define clk     PORTBbits.RB2
#define strobe  PORTBbits.RB3

char rhex = 0;

void initSerial(void); 
void serialOut (unsigned char d);
unsigned char serialIn (void);
void hexToAscii (char dado);
void transmite (void);
char asciiToHex( unsigned char a1, unsigned char a2 );
//void recebe (void);




#endif	

