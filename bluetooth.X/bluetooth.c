#include <xc.h>
#include "eusart.h"
#include "config.h"

void master1(void) 
{
    initEUSART(9600);
    writeString("AT+UART=9600,0,0\r\n");
    writeString("AT+ROLE=1\r\n");                           //Definir função do módulo como escravo
    __delay_ms(100);
    writeString("AT+CMODE=0\r\n");                          //Conecta o modulo a endereço especifico
    __delay_ms(100);
    writeString("AT+INQM=0,5,5\r\n");                       //modo de acesso , número de dispositivos, tempo
    __delay_ms(100);
    writeString("AT+INIT\r\n");                             //Emula um cabo  para prover  conexões seriais RS-232
    __delay_ms(100);
    writeString("AT+INQ\r\n");                              //informação do dispositivo 
    __delay_ms(100);
    writeString("AT+PSWD=\"0910\"\r\n");   
}

void slave1(void) 
{
    initEUSART(9600);  
    writeString("AT+UART=9600,0,0\r\n");
    writeString("AT+RMAAD\r\n");                            //Exclua todos os dispositivos autenticados na lista de pares
    __delay_ms(100);
    writeString("AT+ROLE=0\r\n");                           //Definir função do módulo como escravo
    __delay_ms(100);
    writeString("AT+CMODE=0\r\n");                          //Conecta o modulo a endereço especifico
    __delay_ms(100);
    writeString("AT+INQM=0,5,5\r\n");                       //modo de acesso , número de dispositivos, tempo
    __delay_ms(100);
    writeString("AT+INIT\r\n");
    __delay_ms(100);
    writeString("AT+NAME=\"Escravo\"\r\n");
    __delay_ms(100);
    writeString("AT+PSWD=\"0910\"\r\n");             
    
}

void modulo1(void) 
{
   initEUSART(9600);   
   writeString("AT+PAIR=3DBA,88,687A74,20\r\n");
   __delay_ms(100);
    writeString("AT+LINK=3DBA,88,687A74\r\n");
   __delay_ms(100);
   writeString("AT+BIND=3DBA,88,687A74\r\n");               //Define o endereço do modulo
   __delay_ms(100);   
}


void modulo2(void) 
{
   initEUSART(9600);
   writeString("AT+PAIR=0013,EF,0014BB,20\r\n");
   __delay_ms(100);
   writeString("AT+LINK=0013,EF,0014BB\r\n");
   __delay_ms(100);
   writeString("AT+BIND=0013,EF,0014BB\r\n");               //Define o endereço do modulo
   __delay_ms(100);
}


void modulo3(void) 
{
   initEUSART(9600);
   writeString("AT+PAIR=98D3,B1,FD43E9,20\r\n");
   __delay_ms(100);
   writeString("AT+LINK=98D3,B1,FD43E9\r\n");
   __delay_ms(100);
   writeString("AT+BIND=98D3,B1,FD43E9\r\n");               //Define o endereço do modulo
   __delay_ms(100);
}


void modulo4(void) 
{
//   initUART(9600);
//   writeString("AT+PAIR=         ,20\r\n");
//   __delay_ms(100);
//   writeString("AT+LINK=            \r\n");
//   __delay_ms(100);
//   writeString("AT+BIND=            \r\n");               //Define o endereço do modulo
//   __delay_ms(100);
}

void modulo5(void) 
{
//   initUART(9600);
//   writeString("AT+PAIR=         ,20\r\n");
//   __delay_ms(100);
//   writeString("AT+LINK=            \r\n");
//   __delay_ms(100);
//   writeString("AT+BIND=            \r\n");               //Define o endereço do modulo
//   __delay_ms(100);
}

void modulo6(void) 
{
//   initUART(9600);
//   writeString("AT+PAIR=         ,20\r\n");
//   __delay_ms(100);
//   writeString("AT+LINK=            \r\n");
//   __delay_ms(100);
//   writeString("AT+BIND=            \r\n");               //Define o endereço do modulo
//   __delay_ms(100);
}

void modulo7(void) 
{
//   initUART(9600);
//   writeString("AT+PAIR=         ,20\r\n");
//   __delay_ms(100);
//   writeString("AT+LINK=            \r\n");
//   __delay_ms(100);
//   writeString("AT+BIND=            \r\n");               //Define o endereço do modulo
//   __delay_ms(100);
}

void modulo8(void) 
{
//   initUART(9600);
//   writeString("AT+PAIR=         ,20\r\n");
//   __delay_ms(100);
//   writeString("AT+LINK=            \r\n");
//   __delay_ms(100);
//   writeString("AT+BIND=            \r\n");               //Define o endereço do modulo
//   __delay_ms(100);
}
