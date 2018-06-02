#include <avr/io.h>
#include "lcd_4bit.h"
#include "lcd_customs.h"

void LCD_CreateTilde(unsigned char index)
{
    unsigned char tilde[8] = // ~
    {
        0x00,
        0x00,
        0x00,
        0x08,
        0x15,
        0x02,
        0x00,
        0x00,
    };
    
    LCD_CreateCustom(index, tilde);
}

void LCD_CreateKuu(unsigned char index)
{
    unsigned char kuu[8] = // ãÛ
    {
        0x04,
        0x1F,
        0x11,
        0x0A,
        0x11,
        0x0E,
        0x04,
        0x1F
    };
    
    LCD_CreateCustom(index, kuu);
}

void LCD_CreateHaku(unsigned char index)
{
    unsigned char haku[8] = // îí
    {
        0x00,
        0x04,
        0x08,
        0x1F,
        0x11,
        0x1F,
        0x11,
        0x1F
    };
    
    LCD_CreateCustom(index, haku);
}

void LCD_CreateShou(unsigned char index)
{
    unsigned char shou[8] = // è≠
    {
        0x04,
        0x0E,
        0x15,
        0x04,
        0x09,
        0x01,
        0x06,
        0x18
    };
    
    LCD_CreateCustom(index, shou);
}

void LCD_CreateJo(unsigned char index)
{
    unsigned char jo[8] = // èó
    {
        0x02,
        0x04,
        0x1F,
        0x0A,
        0x11,
        0x0A,
        0x04,
        0x1B
    };
    
    LCD_CreateCustom(index, jo);
}

void LCD_ProgramCustoms()
{
   LCD_CreateTilde(0);
   LCD_CreateKuu(1);
   LCD_CreateHaku(2);
   LCD_CreateShou(3);
   LCD_CreateJo(4);
}