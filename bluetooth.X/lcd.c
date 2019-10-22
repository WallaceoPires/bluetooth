#include <xc.h>
#include "lcd_t.h"
#include "config.h"

volatile LCDbits_t LCD __at(0x08);

void cmdLCD ( unsigned char cmd )
{
    volatile REGnibble_t nibble;
    
    nibble.HILO  = cmd;
    LCD.RS       = 0;
    LCD.BUS      = nibble.HI;
    LCD.EN       = 0; 
    
    if ( cmd == LCD_CLEAR || cmd == LCD_HOME )
        __delay_ms( 5 );
    else
        __delay_us( 40 );
    
    LCD.EN       = 1;
   
        
   if ( cmd != (LCD_DATA_BITS_4) )
   { 
    LCD.RS       = 0;
    LCD.BUS      = nibble.LO;
    LCD.EN       = 0;

    if ( cmd == LCD_CLEAR || cmd == LCD_HOME )
        __delay_ms( 5 );
    else
        __delay_us( 40 );
    
    LCD.EN        = 1;
   }
}

void putLCD ( unsigned char c )
{
    volatile REGnibble_t nibble;
    nibble.HILO = c;
    
    LCD.RS   = 1;
    LCD.BUS  = nibble.HI;
    LCD.EN   = 0; 
    __delay_us(40);
    LCD.EN   = 1;
    
    
    LCD.RS   = 1;
    LCD.BUS  = nibble.LO;
    LCD.EN   = 0; 
    __delay_us(40);
    LCD.EN   = 1;
    
}

void gotoxy ( unsigned char x, unsigned char y )
{
    cmdLCD (( LCD_GOTOL0 | (LCD_GOTOL1 * y ) + ( x & 0x3f )));
}

void writeLCD ( unsigned char x, unsigned char y, const char * ptr )
{
    gotoxy(x,y);
    while( *ptr )
    putLCD(*ptr++);
}

void initLCD ( void )
{
    LCD.BUS           = 0;
    LCD.RS            = 0;
    LCD.EN            = 1;
    TRISD             = 0x00;
        
    __delay_ms( 100 );
    cmdLCD ( LCD_DATA_BITS_4 );
    cmdLCD ( LCD_LINE2 );
    cmdLCD ( LCD_ON /*| LCD_BLINK*/ );
    cmdLCD ( LCD_CLEAR );    
    cmdLCD ( LCD_HOME );    
}    