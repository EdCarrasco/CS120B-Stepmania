#include "../header/uart.h"

#define BAUD_RATE 9600

void UART_init() { Serial.begin(BAUD_RATE); }

bool UART_available() { return Serial.available(); }

unsigned char UART_Peek(void) { return Serial.peek(); }

unsigned char UART_Read(void) { return Serial.read(); }

void UART_Read(unsigned char a[], unsigned char size) { Serial.readBytes(a,size); }

void UART_Write(unsigned char data) { Serial.write(data); }