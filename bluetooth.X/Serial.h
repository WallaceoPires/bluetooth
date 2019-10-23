
#ifndef SERIAL_H
#define	SERIAL_H

#define dout    PORTBbits.RB0
#define din     PORTBbits.RB1
#define clk     PORTBbits.RB2
#define strobe  PORTBbits.RB3



void initSerial(void); 
void serialOut (unsigned char d);
unsigned char serialIn (void);
void convHexToAnsc (char dado);
void transmite (void);
void convAsciToHex (void);
void recebe (void);




#endif	

