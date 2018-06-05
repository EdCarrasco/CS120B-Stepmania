#ifndef __usartSM_h__
#define __usartSM_h__

int Tick_USART(int state);
int (*usart_GetTick())(int);

void send_Controller();

#endif