#include <xc.h>
#include "Serial.h"
#include "config.h"
#include "uart.h"

void initSerial(void) 
{
    PORTB       = 0x00;               // Valor inicial do PORT    
    CCP1CON    &= 0xF0;            // Capture/Compare/PWM of    
    ANSELH      = 0x00;            // Desabilita entradas anologicas      
    TRISB       = 0b00000010;         // Direção de dados 
    
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

void convHexToAnsc (char dado)
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
        convHexToAnsc(serialIn());
        writeUART(tdez);
        writeUART(tuni); 
        comp = serial;
    }
}

void convAsciToHex (void)
{
    char dez;
    char uni;

    if (RCIF)
        dez = readUART();
    
    if(dez > 0x40)
        dez -= 0x37;
    else
        dez -= 0x30;
    
    __delay_ms(200);
    
    if (RCIF)
        uni = readUART();
    
    if(uni > 0x40)
        uni -= 0x37;
    else
        uni -= 0x30;
    
    dez<<=4;
    
    rhex = dez | uni;
    
}

void recebe (void)
{    
    if (RCIF)
    {
        convAsciToHex();
        serialOut(rhex);
        __delay_ms(100);
        RCIF = 0;
    }      
}