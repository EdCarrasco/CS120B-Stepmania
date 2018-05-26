#ifndef __lcd_4bit_h__
#define __lcd_4bit_h__

void LCD_init();
void LCD_ClearScreen(void);
void LCD_WriteCommand (unsigned char Command);
void LCD_WriteData(unsigned char Data);
void LCD_CreateCustom(unsigned char index, const unsigned char Data[8]);
void LCD_Cursor (unsigned char column);
void LCD_DisplayString(unsigned char column ,const unsigned char *string);

#endif