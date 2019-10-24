#include <xc.h>
#include "Serial.h"
#include "config.h"
#include "eusart.h"
#include "fifo.h"

char tuni;
char tdez;


void initSerial(void) 
{
    PORTB       = 0x00;                 // Valor inicial do PORT    
    CCP1CON    &= 0xF0;                 // Capture/Compare/PWM of    
    ANSELH      = 0x00;                 // Desabilita entradas anologicas      
    TRISB       = 0b00000010;           // Direção de dados 
    
    PORTBbits.RB4 = 1;
    serialOut(0x00);
}

void serialOut (unsigned char d)
{
    unsigned char i = 0x80;
    strobe = 0;
    while (i)  
    {
        clk = 0;
        if(d & i )
            dout = 1;
        else
            dout = 0;
        i >>= 1;
        clk = 1;        
    }   
    strobe = 1;
    
}

unsigned char serialIn (void)
{
    unsigned char i = 0x80;
    unsigned char dado = 0;
    strobe = 0;
    strobe = 1;
    while (i)  
    {
        clk = 0; 
        if(din)
            dado |=i;
        i >>=1;
        clk = 1;
    }   
    return(dado);
}

void hexToAscii (char dado)
{
    char dez;
    char uni;
    
    uni = dado & 0x0F;
    dez = dado & 0xF0;
    dez >>= 4 ;
    
    if (uni > 0x09)
        uni += 0x37;
    else
        uni += 0x30;
    
    if (dez > 0x09)
        dez += 0x37;
    else
        dez += 0x30;  
    
    tdez = dez;
    tuni = uni;
}

char comp = 0;
char serial = 0;

void transmite (void)
{ 
    serial = serialIn();
    
    if(serial != comp)
    {
        hexToAscii(serialIn());
        writeEUSART(tdez);
        writeEUSART(tuni); 
        comp = serial;
    }
}



char asciiToHex( unsigned char a1, unsigned char a2 )
{
    char dez;
    char uni;
    
    dez = a1;
    uni = a2;
    
    if(dez > 0x40)
        dez -= 0x37;
    else
        dez -= 0x30;
    
    if(uni > 0x40)
        uni -= 0x37;
    else
        uni -= 0x30;
    
    dez<<=4;
    
    rhex = dez | uni;
    
    return (rhex);
    
}


//void recebe (void)
//{    
//    convAsciToHex();
//    serialOut(rhex);     
//}