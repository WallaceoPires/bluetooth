#include <xc.h>
#include <pic16f887.h>
#include "config.h"
#include "uart.h"

char initUART(unsigned long int baudrate)      //inicili��o comunica��o
{
	unsigned int x;
	x = (_XTAL_FREQ /(baudrate*64))-1;
  
	  TXSTAbits.TXEN    = 1;       // Habilita Transmiss�o
      TXSTAbits.SYNC    = 0;       // Sele��o de modo de comunica��o, 0 = Ass�ncrono
	  TXSTAbits.TX9     = 0;       // Transmiss�o em  8 bits   
      TXSTAbits.TX9D    = 0;       // Sem pariedade     
      RCSTAbits.SPEN    = 1;       // Habilita pinos RC6 e RC7 para comunica��o                
      RCSTAbits.CREN    = 1;       // Habilita recep��o continua  
      RCSTAbits.RX9     = 0;       // Recebe em  8 bits               
      RCSTAbits.RX9D    = 0;       // Sem pariedade 
      
      SSPSTATbits.P     = 1;       // STOP BITS   
      
      TXSTAbits.BRGH    = 0;       // Controle de Baud Rate
      BAUDCTLbits.BRG16 = 0;
      
      SPBRG  = x;                  // Velocidade de Baud Rate
}

char UART_TX_Empty(void)
{
  return TRMT;
}

char UART_Data_Ready(void)
{
   return RCIF;             //verifica a recp��o do mudulo UART
}
char readUART(void)        // l� caractere recebido 
{
    if (RCIF)
    {
        while(!RCIF);             // Enquanto RCIF = 0, aguarda a chegada do caractere
        return RCREG;             // Retorna o caracter recebido
    }
    
}

void readString(char *Output, unsigned int length)
{
	unsigned int i;
	for(int i=0;i<length;i++)
		Output[i] = readUART();
}

void writeUART(char data)   // escreve caracter 
{
    while(!TRMT);             // aguarda a finaliza��o da transmissa� do caractere
    TXREG = data;             // Carrega em TXREG e transmite o caractere via EUART
}

void writeString (char *text)   // escreve frase no endere�o apontado
{
  int i;                
  for(i=0;text[i]!='\0';i++)    // enquanto o conteudo do endere�o "text" for diferente de 0
	  writeUART(text[i]);       // executa a fun��o escreve caracter
}

