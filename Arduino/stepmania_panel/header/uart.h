#ifndef __uart_h__
#define __uart_h__

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

void UART_init();
bool UART_available();
unsigned char UART_Peek(void);
unsigned char UART_Read(void);
void UART_Read(unsigned char a[], unsigned char size);
void UART_Write(unsigned char data);

#endif