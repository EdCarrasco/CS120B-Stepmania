/*
 * stepmania.c
 *
 * Created: 2018-05-25 15:25:30
 *  Author: JonathanOaks
 */ 

#define F_CPU 8000000UL // Clock Definition 8MHz

#include <avr/io.h>
#include <util/delay.h>
#include "lcd_4bit.c"
#include "snes.c"

int main(void)
{
    DDRA = 0xFE; PORTA = 0x01;
    DDRC = 0xFF; PORTC = 0x00;
    
    LCD_init();
    LCD_Cursor(17);
    LCD_WriteData('Z');

    while(1) {
        unsigned short data = snes_GetData();
        _delay_ms(25); //<-- change this delay
        
        for(unsigned char i = 0; i < 12; i++)
        {
            LCD_Cursor(i+1);
            if(data & (1 << i))
            {
                LCD_WriteData('A'+i);
            }
            else
            {
                LCD_WriteData(' ');
            }
        }
    }
    
    return 0;
}