
#include <xc.h>

void initBT (void)
{
    
    TRISCbits.TRISC0 = 1;
    TRISCbits.TRISC1 = 1;
    TRISCbits.TRISC2 = 1;
    
    PORTCbits.RC0       = 0;
    PORTCbits.RC1       = 0;
    PORTCbits.RC2       = 0;
    
}

char B1 ( void )
{
    return ( PORTCbits.RC1 );
}
char B2( void )
{
    return ( PORTCbits.RC2 );
}
char B3( void )
{
    return ( PORTCbits.RC0 );
}


// --------------------------------------------------------
       
char estadoAnteriorB1 = 0 ;
char bordaSubidaB1 ( void )
{
    char estadoAtualB1;
    char resp;
    
    estadoAtualB1 = B1();
    
    if( (estadoAtualB1 == 0) && (estadoAnteriorB1 == 1) )
        resp = 1;
    else
        resp = 0;
    estadoAnteriorB1 = estadoAtualB1;
    return ( resp );
}
// --------------------------------------------------------
       
char estadoAnteriorB2 = 0 ;
char bordaSubidaB2 ( void )
{
    char estadoAtualB2;
    char resp1;
    
    estadoAtualB2 = B2();
    
    if( (estadoAtualB2 == 0) && (estadoAnteriorB2 == 1) )
        resp1 = 1;
    else
        resp1 = 0;
    estadoAnteriorB2 = estadoAtualB2;
    return ( resp1 );
} 
// --------------------------------------------------------
       
char estadoAnteriorB3 = 0 ;
char bordaSubidaB3 ( void )
{
    char estadoAtualB3;
    char resp2;
    
    estadoAtualB3 = B3();
    
    if( (estadoAtualB3 == 0) && (estadoAnteriorB3 == 1) )
        resp2 = 1;
    else
        resp2 = 0;
    estadoAnteriorB3 = estadoAtualB3;
    return ( resp2 );
} 