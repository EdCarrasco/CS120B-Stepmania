#include "lcdSM.h"
#include "lcd_4bit.h"
#include "lcd_customs.h"

#include "globals.h"

enum LCD_States {lcd_Start, lcd_Off, lcd_Update};
int Tick_LCD(int state)
{
    switch(state) // Transitions
    {
        case lcd_Start:
            LCD_ProgramCustoms();
			LCD_Cursor(1);
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

			LCD_Cursor(17);
			LCD_WriteData('C');
			LCD_WriteData('o');
			LCD_WriteData('m');
			LCD_WriteData('b');
			LCD_WriteData('o');

			LCD_Cursor(26);
			LCD_WriteData('H');
			LCD_WriteData('i');
			LCD_WriteData('t');
			LCD_WriteData('s');
            state = lcd_Off;
            break;
        case lcd_Off:
			state = (get_PlayEnable()) ? lcd_Update : lcd_Off;
            break;
		case lcd_Update:
			state = (get_PlayEnable()) ? lcd_Update : lcd_Off;
			break;
        default:
            state = lcd_Start;
            break;
    }
    
    switch(state) // Actions
    {
        case lcd_Start: break;
		case lcd_Off:
			LCD_Cursor(22);
			WriteScore(get_Max_Combo());
			LCD_Cursor(30);
			WriteScore(get_Max_Hits());
			break;
		case lcd_Update:
			LCD_Cursor(22);
			WriteScore(get_Combo());
			LCD_Cursor(30);
			WriteScore(get_Hits());
			break;
    }
    
    return state;
}

int (*lcd_GetTick())(int) { return Tick_LCD; }

void WriteScore(unsigned char score)
{
	unsigned char hundreds = 0;
	unsigned char tens = 0;
	unsigned char ones = 0;
	
	while(score >= 100)
	{
		score-=100;
		hundreds++;
	}
	while(score >= 10)
	{
		score-=10;
		tens++;
	}
	while(score > 0)
	{
		score--;
		ones++;
	}

	if(hundreds > 0)
	{
		LCD_WriteData(('0' + hundreds));
		LCD_WriteData(('0' + tens));
		LCD_WriteData(('0' + ones));
	}
	else if(tens > 0)
	{
		LCD_WriteData((' '));
		LCD_WriteData(('0' + tens));
		LCD_WriteData(('0' + ones));
	}
	else
	{
		LCD_WriteData((' '));
		LCD_WriteData((' '));
		LCD_WriteData(('0' + ones));
	}
}