#include <xc.h>                                                                 // Aciona Biblioteca desejada.
#include "bds.h"                                                                // Aciona Biblioteca desejada.
#include "config.h"                                                             // Aciona Biblioteca desejada.
#include "lcd_t.h"                                                              // Aciona Biblioteca desejada.
#include "auxiliar.h"                                                           // Aciona Biblioteca desejada.
#include "timer0.h"                                                             // Aciona Biblioteca desejada.
#include "eusart.h"                                                             // Aciona Biblioteca desejada.
#include "bluetooth.h"                                                          // Aciona Biblioteca desejada.
#include "Serial.h"
#include "fifo.h"

void __interrupt() geral( void )
{
    INTCONbits.GIE = 0;

    if( PIE1bits.RCIE && PIR1bits.RCIF )
    {
        interrupt_EUSART_RX();
    }
    
    if( INTCONbits.T0IE && INTCONbits.T0IF )
    {
        INTCONbits.T0IF = 0;
        intt0_1ms();
    }
    
    INTCONbits.GIE = 1;
}

void main(void) 
{
    initBT();                                                                   // Inicialização dos Botões.
    initLCD();                                                                  // Inicialização do LCD para 4Bits.
    initTimer0();                                                               // Inicialização do Timer0. 
    initEUSART(9600);                                                           // Inicialização da Comunicação UART.
    initSerial();
    
    
    unsigned int aux = 210;                                                       // Variavel de modelo Interiro.
    unsigned char a  = 0;                                                       // Variavel de modelo Char.
    unsigned char i  = 0;                                                       // Variavel de modelo Char.
    
    while(1)                                                                    // Loop
    {
        switch (aux)                                                            // Verifica a variavel.
        {
            case 0 :                                                            // Caso a variavel valer o numero desejado, executa os comandos.
                logo();                                                         // Sub-rotina - Texto de Inicialização.
                aux = 1;                                                        // Devine numero da variavel.
                break;                                                              
            
            case 1:                                                             // Caso a variavel valer o numero desejado, executa os comandos.
                textConfig();                                                    // Sub-rotina - Texto esteira.
                aux = 10;                                                       // Devine numero da variavel.
                break;
               
            case 2:                                                             // Caso a variavel valer o numero desejado, executa os comandos.
                textCMdat();                                                    // Sub-rotina - Texto pareamento.
                aux = 20;                                                       // Devine numero da variavel. 
                break;
                
            case 3:                                                             // Caso a variavel valer o numero desejado, executa os comandos.
                textCMpar();                                                    // Sub-rotina - Texto pareamento.
                aux = 30;                                                       // Devine numero da variavel. 
                break;
                
/*---------------------------Configuração de Menus----------------------------*/              
                
            case 10:                                                            // Menu para o modulo /*Master*/
                if(bordaSubidaB1())     aux = 2;                                // Avança tela do LCD em função da borda do Botão.
                if(bordaSubidaB2())     aux = 3;                                // Retorna tela do LCD em função da borda do Botão.
                if(bordaSubidaB3())     aux = 100;                              // Abre tela de configuração.           
                break;
               
            case 20:                                                            // Menu para o modulo do CLP /*Slave*/
                if(bordaSubidaB1())     aux = 3;                                // Avança tela do LCD em função da borda do Botão.
                if(bordaSubidaB2())     aux = 1;                                // Retorna tela do LCD em função da borda do Botão.
                if(bordaSubidaB3())     aux = 200;                              // Abre tela de configuração do CLP.
                break;
               
            case 30:                                                            // Menu de Pareamento
                if(bordaSubidaB1())     aux = 1;                                // Avança tela do LCD em função da borda do Botão.
                if(bordaSubidaB2())     aux = 2;                                // Retorna tela do LCD em função da borda do Botão.
                if(bordaSubidaB3())     aux = 300;                              // Abre tela de configuração para pareamento.
                if(B2() & B3())         aux = 666;                              // subliminal message
                break;
 
/*-----------------------Configuração de IP para Esteira----------------------*/                
                
            case 100:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0,"MODULO  DESEJADO");
                writeLCD(0,1,"ESTEIRA      CLP");
                aux = 110;
                break;
                    
            case 110:
                switch(i)
                {
                    case 0:
                        textSelectionEST();
                        if(bordaSubidaB2()) i = 1;
                        if(bordaSubidaB3()) aux = 111;
                        if(B1() & B2())     aux = 10;
                        break;
                       
                    case 1:
                        textSelectionCLP();
                        if(bordaSubidaB1()) i=0;
                        if(bordaSubidaB3()) aux = 112;
                        if(B1() & B2())     aux = 10;
                        break;
                       
                }    
                break;
           
            case 111:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0," Enviando ");
                writeLCD(0,1," P/ Esteira ");
                slave1();
                textLoading();
                aux = 1;  
                break;
                
            case 112:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0," Enviando ");
                writeLCD(0,1," P/ CLP ");
                master1();
                textLoading();
                aux = 1;  
                break;
                

            
 /*----------------------------------------------------------------------------*/           
            
            case 200:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0," CONFIRMA TROCA "); /* PARA ESCRAVO */
                writeLCD(0,1,"    DE DADOS    ");
                aux = 210;
                break;
                    
            case 210:
//                if(B1() & B2()) aux = 20;
//                if(bordaSubidaB3())
                {
                    cmdLCD(LCD_CLEAR);
                    writeLCD(0,0,"    TROCANDO    ");
                    writeLCD(0,1,"   INFORMACAO   ");
                    
                    char t = 1; 
                    
                    PORTBbits.RB4 = 0;
                    
                    while(t)
                    {
                        switch( errorRxEUSART() )
                        {
                            case 2: writeLCD(0,1, "Overrun Error");
                                    resetErrorRxEUSART();
                                    break;
                            case 1: writeLCD(0,1, "Framing Error");
                                    resetErrorRxEUSART();
                                    break;
                            default:
                            case 0:
                                
                                if( statusFIFO() >= 2 )
                                {
                                    unsigned char a1 = getFIFO();
                                    unsigned char a2 = getFIFO();
                                   serialOut( asciiToHex( a1, a2 ) );
                                    
                                }
                            break;
                        }
                        
                        serialOut(rhex);
                        transmite();
                        
//                        if(B1() & B2()) t = 0;
                    }
                    PORTBbits.RB4 = 1;
                    aux = 2;
                }   
                break;
 
/*----------------------------------------------------------------------------*/
                
            case 300:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0,"BLUETOOTH <---->");
                aux = 301;
                break;
            
            case 301:
                writeLCD(0,1,"PAREAR      BT  ");
                if(bordaSubidaB1() || bordaSubidaB2()) aux = 302;
                if(bordaSubidaB3()) aux = 305;
                 if(B1() & B2()) aux = 30;
                break;
                
            case 302:
                writeLCD(0,1,"DESCONECTAR BT  ");
                if(bordaSubidaB1() || bordaSubidaB2()) aux = 301;
                if(bordaSubidaB3()) aux = 306;
                 if(B1() & B2()) aux = 30;
                break;
            
            
            case 305:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0," PAREAR COM IP  ");
                writeLCD(0,1,"1 2 3 4  5 6 7 8");
                aux = 310;
                break;
                
            case 306:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0,"DESCONECTANDO   ");
                //writeLCD(0,1,"");
                __delay_ms(500);
                aux = 3;
                break;
                    
                    
            case 310:
                switch(a)
                {
                    case 0:
                        textSelection1();
                        if(bordaSubidaB1()) a=7;
                        if(bordaSubidaB2()) a=1;
                        if(bordaSubidaB3()) aux = 311;
                        if(B1() & B2()) aux = 30;
                        break;
                       
                    case 1:
                        textSelection2();
                        if(bordaSubidaB1()) a=0;
                        if(bordaSubidaB2()) a=2;
                        if(bordaSubidaB3()) aux = 312;
                        if(B1() & B2()) aux = 30;
                        break;
                       
                    case 2:
                        textSelection3();
                        if(bordaSubidaB1()) a=1;
                        if(bordaSubidaB2()) a=3;
                        if(bordaSubidaB3()) aux = 313;
                        if(B1() & B2()) aux = 30;
                        break;
                       
                    case 3:
                        textSelection4();
                        if(bordaSubidaB1()) a=2;
                        if(bordaSubidaB2()) a=4;
                        if(bordaSubidaB3()) aux = 314;
                        if(B1() & B2()) aux = 30;
                        break;
                       
                    case 4:
                        textSelection5();
                        if(bordaSubidaB1()) a=3;
                        if(bordaSubidaB2()) a=5;
                        if(bordaSubidaB3()) aux = 315;
                        if(B1() & B2()) aux = 30;
                        break;
                       
                    case 5:
                        textSelection6();
                        if(bordaSubidaB1()) a=4;
                        if(bordaSubidaB2()) a=6;
                        if(bordaSubidaB3()) aux = 316;
                        if(B1() & B2()) aux = 30;
                        break;
                       
                    case 6:
                        textSelection7();
                        if(bordaSubidaB1()) a=5;
                        if(bordaSubidaB2()) a=7;
                        if(bordaSubidaB3()) aux = 317;
                        if(B1() & B2()) aux = 30;
                        break;
                       
                    case 7:
                        textSelection8();
                        if(bordaSubidaB1()) a=6;
                        if(bordaSubidaB2()) a=0;
                        if(bordaSubidaB3()) aux = 318;
                        if(B1() & B2()) aux = 30;
                        break;
                }   
                break;        
            
            case 311:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0," Enviando ");
                //master1();
                textLoading();
                aux = 3;  
                break;
                
            case 312:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0," Enviando ");
                //master1();
                textLoading();
                aux = 3;  
                break;
                
            case 313:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0," Enviando ");
                //master1();
                textLoading();
                aux = 3;  
                break;
                
            case 314:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0," Enviando ");
                //master1();
                textLoading();
                aux = 3;  
                break;
                
            case 315:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0," Enviando ");
               // master1();
                textLoading();
                aux = 3;  
                break;
                
            case 316:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0," Enviando ");
                //master1();
                textLoading();
                aux = 3;  
                break;
                
            case 317:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0," Enviando ");
                //master1();
                textLoading();
                aux = 3;  
                break;
                
                case 318:
                cmdLCD(LCD_CLEAR);
                writeLCD(0,0," Enviando ");
                //master1();
                textLoading();
                aux = 3;  
                break;
                
/*----------------------------------------------------------------------------*/           
            
            case 666:
                easterEgg();
                aux = 0;
                break;
        }
    }
}