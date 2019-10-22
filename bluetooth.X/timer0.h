#ifndef TIMER0_H
#define	TIMER0_H

void intt0_1ms( void );              // Configura "estouro" para 1mS e reset contagem
void setT0( int c );                 // Valor a ser configurado para setar, tempo 
int statusT0( void );                // Ler valor do "tempo" contado
void setT0limite( int c );          // Valor a ser configurado para Limite 
int statusT0limite( void );         // Ler valor configurado para Limite 
void initTimer0( void );

#endif

