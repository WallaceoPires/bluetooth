#include <xc.h>
#include <pic16f887.h>
#include "config.h"
#include "uart.h"

char initUART(unsigned long int baudrate)      //inicilição comunicação
{
	unsigned int x;
	x = (_XTAL_FREQ /(baudrate*64))-1;
  
	  TXSTAbits.TXEN    = 1;       // Habilita Transmissão
      TXSTAbits.SYNC    = 0;       // Seleção de modo de comunicação, 0 = Assíncrono
	  TXSTAbits.TX9     = 0;       // Transmissão em  8 bits   
      TXSTAbits.TX9D    = 0;       // Sem pariedade     
      RCSTAbits.SPEN    = 1;       // Habilita pinos RC6 e RC7 para comunicação                
      RCSTAbits.CREN    = 1;       // Habilita recepção continua  
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
   return RCIF;             //verifica a recpção do mudulo UART
}
char readUART(void)        // lê caractere recebido 
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
    while(!TRMT);             // aguarda a finalização da transmissaõ do caractere
    TXREG = data;             // Carrega em TXREG e transmite o caractere via EUART
}

void writeString (char *text)   // escreve frase no endereço apontado
{
  int i;                
  for(i=0;text[i]!='\0';i++)    // enquanto o conteudo do endereço "text" for diferente de 0
	  writeUART(text[i]);       // executa a função escreve caracter
}

