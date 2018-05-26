#include "lcdSM.h"
#include "lcd_4bit.h"
#include "lcd_customs.h"

#include "globals.h"

enum LCD_States {lcd_Start, lcd_Update};
int Tick_LCD(int state)
{
    switch(state) // Transitions
    {
        case lcd_Start:
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
            state = lcd_Update;
            break;
        case lcd_Update:
            state = lcd_Update;
            break;
        default:
            state = lcd_Start;
            break;
    }
    
    switch(state) // Actions
    {
        case lcd_Start: break;
        case lcd_Update:
            for(unsigned char i = 0; i < 12; i++)
            {
                LCD_Cursor(i+17);
                if(get_ControllerData() & (1 << i))
                {
                    LCD_WriteData('A'+i);
                }
                else
                {
                    LCD_WriteData(' ');
                }
            }
            break;
    }
    
    return state;
}

int (*lcd_GetTick())(int) { return Tick_LCD; }