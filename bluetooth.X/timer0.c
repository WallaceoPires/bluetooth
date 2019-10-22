#include <xc.h>
#include <pic16f887.h>
#include "config.h"
#include "timer0.h"

int t0final = 0;
int t0cont;

void __interrupt() interrup(void)
{
    if( INTCONbits.T0IE && INTCONbits.T0IF )
    {
        INTCONbits.T0IF = 0;
        intt0_1ms();
    }
}

void intt0_1ms( void )              // Configura "estouro" para 1mS e reset contagem
{
    TMR0 = 100;                     // Ajusta o overflows 
    
    if( ++t0cont >= t0final )       // Compara tempo contado com programado
    {
        t0cont = 0;
    }
}

void setT0( int c )                 // Valor a ser configurado para setar, tempo 
{
    t0cont = c;
}

int statusT0( void )                // Ler valor do "tempo" contado
{
    return( t0cont );
}

void setT0limite( int c )          // Valor a ser configurado para Limite 
{                                  
    t0final = c;                    
}                                   
int statusT0limite( void )         // Ler valor configurado para Limite 
{
    return( t0final );
}

void initTimer0( void )
{
    
    INTCONbits.GIE = 0;           // Desabilitação de interrupção global
    
    ANSEL         = 0x00;         // Define 
    TRISAbits.TRISA4 = 1;
    
    OPTION_REGbits.T0CS = 0;      // Define clock externo
    
    OPTION_REGbits.PSA = 0;       // Habilita prescaler
    OPTION_REGbits.PS2 = 1;       
    OPTION_REGbits.PS1 = 0;       
    OPTION_REGbits.PS0 = 0;  
    
    OPTION_REGbits.T0SE = 1;   //tipo de borda 1 descida 0 subida
                                  
    TMR0 = 100;                   // Ajusta o overflow
                                  
    setT0limite( 700 );          // Pre determina o valor de comparação para contagem
                                  
    INTCONbits.T0IE = 1;          // Habilitação de estouro TMR0    
    INTCONbits.GIE = 1;           // Habilitação de interrupção global
    
    
}

