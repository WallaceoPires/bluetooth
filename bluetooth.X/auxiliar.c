#include <xc.h>
#include "lcd_t.h"
#include "config.h"
#include "timer0.h"
#include "bds.h"


void logo (void)
{
    cmdLCD(LCD_CLEAR);
    writeLCD(0,0,"__            __");   __delay_ms(200);
    writeLCD(6,0,"B");                  __delay_ms(600);
    writeLCD(7,0,"l");                  __delay_ms(600);
    writeLCD(8,0,"u");                  __delay_ms(600);
    writeLCD(9,0,"e");                  __delay_ms(600);
    writeLCD(0,1,"    Tecnolog    ");   __delay_ms(2500);
}
void textConfig (void)
{
    cmdLCD(LCD_CLEAR);
    writeLCD(0,0,"   Configurar   ");
    writeLCD(0,1,"   ----------   "); 
}

void textCMpar (void)
{
    cmdLCD(LCD_CLEAR);
    writeLCD(0,0,"   Pareamento   ");
    writeLCD(0,1,"   ----------   ");
}

void textCMdat (void)
{
    cmdLCD(LCD_CLEAR);
    writeLCD(0,0," Envio de Dados ");
    writeLCD(0,1,"   ----------   ");
}

void textSelection1 (void)
{   
    writeLCD(15,1,"8");
    writeLCD(2,1,"2");
    if( statusT0() < ( statusT0limite()/2 ) )
    writeLCD(0,1," ");
    else
    writeLCD(0,1,"1");

}

void textSelection2 (void)
{   
    writeLCD(0,1,"1");
    writeLCD(4,1,"3");
    if( statusT0() < ( statusT0limite()/2 ) )
    writeLCD(2,1," ");
    else
    writeLCD(2,1,"2");
}

void textSelection3 (void)
{   
    writeLCD(2,1,"2");
    writeLCD(6,1,"4");;
    if( statusT0() < ( statusT0limite()/2 ) )
    writeLCD(4,1," ");
    else
    writeLCD(4,1,"3");
}

void textSelection4 (void)
{   
    writeLCD(4,1,"3");
    writeLCD(9,1,"5");
    if( statusT0() < ( statusT0limite()/2 ) )
    writeLCD(6,1," ");
    else
    writeLCD(6,1,"4");
}

void textSelection5 (void)
{   
    writeLCD(6,1,"4");
    writeLCD(11,1,"6");
    if( statusT0() < ( statusT0limite()/2 ) )
    writeLCD(9,1," ");
    else
    writeLCD(9,1,"5");
}

void textSelection6 (void)
{   
    writeLCD(9,1,"5");
    writeLCD(13,1,"7");
    if( statusT0() < ( statusT0limite()/2 ) )
    writeLCD(11,1," ");
    else
    writeLCD(11,1,"6");
}

void textSelection7 (void)
{   
    writeLCD(11,1,"6");
    writeLCD(15,1,"8");
    if( statusT0() < ( statusT0limite()/2 ) )
    writeLCD(13,1," ");
    else
    writeLCD(13,1,"7");
}

void textSelection8 (void)
{   ;
    writeLCD(13,1,"7");
    writeLCD(0,1,"1");
    if( statusT0() < ( statusT0limite()/2 ) )
    writeLCD(15,1," ");
    else
    writeLCD(15,1,"8");
}

void textSelectionEST (void)
{   
    writeLCD(13,1,"CLP");
    if( statusT0() < ( statusT0limite()/2 ) )
    writeLCD(0,1,"       ");
    else
    writeLCD(0,1,"ESTEIRA");
}
void textSelectionCLP (void)
{   
    writeLCD(0,1,"ESTEIRA");
    if( statusT0() < ( statusT0limite()/2 ) )
    writeLCD(13,1,"   ");
    else
    writeLCD(13,1,"CLP");
}

void textSelectionPAR (void)
{   
    writeLCD(0,1,"PAREAR");
    if( statusT0() < ( statusT0limite()/2 ) )
    writeLCD(13,1,"   ");
    else
    writeLCD(13,1,"");
}

void textSelectionDES (void)
{   
    writeLCD(0,1,"ESTEIRA");
    if( statusT0() < ( statusT0limite()/2 ) )
    writeLCD(13,1,"   ");
    else
    writeLCD(13,1,"CLP");
}


void textLoading (void)
{
        writeLCD(9,0,".  ");
        __delay_ms(500);
        writeLCD(9,0," . ");
        __delay_ms(500);
        writeLCD(9,0,"  .");
        __delay_ms(500);
        writeLCD(9,0,".  ");
        __delay_ms(500);
        writeLCD(9,0," . ");
        __delay_ms(500);
        writeLCD(9,0,"  .");
        __delay_ms(500);

        writeLCD(9,0,".  ");
        __delay_ms(500);
        writeLCD(9,0,".. ");
        __delay_ms(500);
        writeLCD(9,0,"...");
        __delay_ms(700);
}

void easterEgg (void)

{
    cmdLCD(LCD_CLEAR);
    
    writeLCD(0,0,"WALLACE PIRES   ");__delay_ms(1000);
    writeLCD(0,1,"MATEUS PINHEIRO ");__delay_ms(1000);
    writeLCD(0,0,"                ");
    writeLCD(0,0,"GUI. RIBEIRO    ");__delay_ms(1000);
    writeLCD(0,1,"                ");
    writeLCD(0,1,"GABRIEL GENU     ");__delay_ms(1000);
    writeLCD(0,0,"                ");
    writeLCD(0,0,"LINCON NOVAIS   ");__delay_ms(1000);
    writeLCD(0,1,"                ");__delay_ms(300);
    
    cmdLCD(LCD_CLEAR);__delay_ms(200);
    writeLCD(0,0,"      ARRI      ");__delay_ms(500);
    writeLCD(0,1,"     EGUAAA     ");__delay_ms(2500);
    cmdLCD(LCD_CLEAR);__delay_ms(200);
    writeLCD(0,0,"XD *-*ARRI*-* XD");
    writeLCD(0,1,"!*-* EGUAAA *-*!");__delay_ms(1000);
    writeLCD(0,0,"50    ARRI    13");
    writeLCD(0,1,"13   EGUAAA   50");__delay_ms(700);
    writeLCD(0,0,":3 *-*ARRI*-* XD");
    writeLCD(0,1,"!*-* EGUAAA *-*!");__delay_ms(1000);
    cmdLCD(LCD_CLEAR);__delay_ms(200);
    
    bordaSubidaB2();
    bordaSubidaB3();
    
}
