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
#include "lcd_customs.c"
#include "snes.c"

int main(void)
{
    DDRA = 0xFE; PORTA = 0x01;
    DDRC = 0xFF; PORTC = 0x00;
    
    LCD_init();
    LCD_ProgramCustoms();
    LCD_WriteData('T');
    LCD_WriteData('a');
    LCD_WriteData('b');
    LCD_WriteData('u');
    LCD_WriteData('l');
    LCD_WriteData('a');
    LCD_WriteData(' ');
    LCD_WriteData('R');
    LCD_WriteData('a');
    LCD_WriteData('s');
    LCD_WriteData('a');
    LCD_WriteData(0);
    LCD_WriteData(1);
    LCD_WriteData(2);
    LCD_WriteData(3);
    LCD_WriteData(4);

    while(1) {
        unsigned short data = snes_GetData();
        _delay_ms(25); //<-- change this delay
        
        for(unsigned char i = 0; i < 12; i++)
        {
            LCD_Cursor(i+17);
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