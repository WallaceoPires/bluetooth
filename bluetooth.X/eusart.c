/*
 * File:   eusart.c
 * Author: curtaeletronica
 *
 * Created on 2 de Outubro de 2019, 20:25
 * 
 * Objetivo: 
 *      Camada de Abstração de Hardware:
 *          Interface de comunicação Serial EUSART
 *          EUSART = Enhanced Universal Synchronous Asynchronous Receiver Transmitter
 *                   Transmissor Receptor Assíncrono Síncrono Universal Aprimorado
 * 
 * Pinos    |nº     |Conexão
 *  RC6     |25     | TX
 *  RC7     |26     | RX
 * 
 */


//***************** Bibliotecas
#include <xc.h>
#include "config.h"
#include "fifo.h"

//***************** Structs
typedef union 
{
    struct 
    {
        unsigned char LO;
        unsigned char HI;
    };
    struct
    {
        unsigned int u16;
    };
} SPBRbits_t;
extern volatile SPBRbits_t SPBRbits @ 0x099;



/****************** Função statusRxEUSART
 * Entrada: -
 * Retorno: 0 = dado não recebido.
 *          1 = dado recebido.
 * Objetivo: Verificar se algum dado foi recebido pelo canal de comunicação.
 */
unsigned char statusRxEUSART( void )
{
    return( statusFIFO() );
}

/****************** Função rxEUSART
 * Entrada: -
 * Retorno: Dado.
 * Objetivo: Ler o valor recebido pelo canal de comunicação serial.
 */
unsigned char readEUSART( void )          // lê caracter recebido
{
    return( getFIFO() );                // pegue
}


/****************** Função rxErrorEUSART
 * Entrada: -
 * Retorno: 0 = sem erro.
 *          1 = Framing Error: Erro no pacote de dados.
 *          2 = Overrun Error: Dado recebido de forma sobreposta, ou seja,
 *              um dado chegou antes do anterior ser lido.
 * Objetivo: Verificar se houve erro na recepção de dados.
 */
unsigned char errorRxEUSART( void )
{
    if( RCSTAbits.FERR )
        return( 1 );
    else if( RCSTAbits.OERR )
        return( 2 );
    else 
        return( 0 );
}


/****************** Procedimento resetErrorRxEUSART
 * Entrada: -
 * Retorno: -
 * Objetivo: Reinicializar/limpar os indicadores(flags) de erro.
 */
void resetErrorRxEUSART( void )
{
    unsigned char aux;
    
    if( RCSTAbits.FERR )            // se houver erro de enquadramento de recebimento
    {
        RCSTAbits.SPEN = 0;
        __delay_ms(100);
        RCSTAbits.SPEN = 1;
    }
    if( RCSTAbits.OERR )            // se houver erro de saturação de recebimento
    {
        RCSTAbits.CREN = 0;
        __delay_ms(100);
        RCSTAbits.CREN = 1;
    }
}



/****************** Procedimento writeEUSART
 * Entrada: dado.
 * Retorno: -
 * Objetivo: Transmitir um dado pelo canal de comunicação serial.
 */
void writeEUSART( unsigned char d )    // escreve caracter
{
    TXREG = d;                      // Carrega em TXREG a variavel d e transmite o caractere via EUART
}


/****************** Função statusTxEUSART
 * Entrada: -
 * Retorno: 1 : transmitindo.
 *          0 : livre.
 * Objetivo: Indicar que um dado está sendo transmitido.
 */
unsigned char statusTxEUSART( void )
{
    return( !TXSTAbits.TRMT );
}


/****************** Procedimento writeString
 * Entrada: String
 * Retorno: -
 * Objetivo: Envia sequencia de caracteres (string) pelo canal de comunicação serial.
 */
void writeString( const char * str )     // escreve frase no vetor apontado
{
    while( *str )                       // enquanto o endereço apontado for verdadeira
    {
        while( !TXSTAbits.TRMT )        // enqunto houver caracter sendo transmitido
            ;
        writeEUSART( *str );               // escrevo o caracter que apontado
        ++str;                          // incremento o ponteiro
    }
    
}



/****************** Procedimento initEUSART
 * Entrada: -
 * Retorno: -
 * Objetivo: Inicializar periférico de comunicação serial assíncrona.
 */
void initEUSART( unsigned long int baudRate )
{
                            // Calcula valor para registradores que produzem
                            // a taxa de transmissão (Baud rate) de dados desejada.
    SPBRbits.u16 = (unsigned int)( (_XTAL_FREQ / (baudRate<<2)) - 1);
    
    TXSTAbits.SYNC = 0;     // Modo assíncrono.
    BAUDCTLbits.BRG16 = 1;  // Gerador de BaudRate de 16 bits.
    TXSTAbits.BRGH    = 1;     // Seleção de alto BaudRate.
    
    RCSTAbits.SPEN = 1;     // Habilita pinos para TX e RX.
    TXSTAbits.TXEN = 1;     // Inicia transmissão.
    RCSTAbits.CREN = 1;     // Habilita recepção.
    
    TXSTAbits.TX9     = 0;       // Transmissão em  8 bits   
    TXSTAbits.TX9D    = 0;       // Sem pariedade
    RCSTAbits.RX9     = 0;       // Recebe em  8 bits               
    RCSTAbits.RX9D    = 0;       // Sem pariedade 
      
    SSPSTATbits.P     = 1;       // STOP BITS
    
    PIE1bits.RCIE = 1;         //EUSART receber bit de ativação de interrupção
    INTCONbits.PEIE = 1;       //Bit de ativação de interrupção periférica
    INTCONbits.GIE = 1;        // interrupção global
    
}


void interrupt_EUSART_RX( void )
{
    if( RCSTAbits.FERR )        // se houver erro de enquadramento de recebimento
    {
        RCSTAbits.SPEN = 0;     // desabilita pinos RC6 e RC7 para comunicação 
    }
    else if( RCSTAbits.OERR )   // se houver erro de saturação de recebimento
    {
        RCSTAbits.CREN = 0;     // desabilita recepção.
    }
    else
        putFIFO( RCREG );

    RCSTAbits.SPEN = 1;         //
    RCSTAbits.CREN = 1;         //
}