#include "../header/matrix.h"

#include <RGBmatrixPanel.h> // Hardware-specific library
#include <Adafruit_GFX.h>   // Core graphics library

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A,B,C,CLK,LAT,OE,false);

void matrix_init(void)
{
    matrix.begin();
    for (uint8_t y = 0; y < 16; y++)
    {
        matrix_DrawPixel(24, y, 20, 20, 20);
        matrix_DrawPixel(26, y, 20, 20, 20);
    }
}

void matrix_DrawPixel(unsigned char x, unsigned char y, unsigned char colors[3]) { matrix.drawPixel(x,y,matrix.Color888(colors[0],colors[1],colors[2])); }

void matrix_DrawPixel(unsigned char x, unsigned char y, unsigned char r, unsigned char g, unsigned char b) { matrix.drawPixel(x,y,matrix.Color888(r,g,b)); }