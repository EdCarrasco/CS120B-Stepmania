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

void matrix_init(void) { matrix.begin(); }

void matrix_DrawPixel(unsigned char x, unsigned char y, unsigned char r, unsigned char g, unsigned char b) { matrix.drawPixel(x,y,matrix.Color888(r,g,b)); }