#ifndef __lcdSM_h__
#define __lcdSM_h__

int Tick_LCD(int state);
int (*lcd_GetTick())(int);
void WriteScore(unsigned char score);

#endif