#include "../header/buttonSM.h"
#include "../header/matrix.h"

#include "../header/globals.h"

#define BUTTONS 4

enum button_States {button_Start, button_Update};
int Tick_Button(int state)
{
    unsigned char controller_data;
    unsigned char button_state;
    
    switch(state) // Transitions
    {
        case button_Start:
            for(unsigned char i = 0; i < BUTTONS; i++)
            {
                button_states[i] = 0;
            }
            state = button_Update;
            break;
        case button_Update:
            state = button_Update;
            break;
        default:
            state = button_Start;
    }
    
    switch(state) // Actions
    {
        case button_Start:
            break;
        case button_Update:
            controller_data = get_ControllerData();
            
            // Left or Y
            if ( (controller_data & 0x01) || (controller_data & 0x10) )
            {
                button_state = get_ButtonState(0);
                if(button_state < 2)
                {
                  set_ButtonState(0, button_state+1);
                }
                matrix_DrawPixel(28, 14, 0, 255, 0);
                matrix_DrawPixel(29, 15, 0, 255, 0);
                matrix_DrawPixel(30, 14, 0, 255, 0);
            }
            else
            {
                set_ButtonState(0,0);
                matrix_DrawPixel(28, 14, 0, 25, 0);
                matrix_DrawPixel(29, 15, 0, 25, 0);
                matrix_DrawPixel(30, 14, 0, 25, 0);
            }

            // Down or B
            if ( (controller_data & 0x02) || (controller_data & 0x20) )
            {
                button_state = get_ButtonState(1);
                if(button_state < 2)
                {
                  set_ButtonState(1, button_state+1);
                }
                matrix_DrawPixel(29, 9, 255, 150, 0);
                matrix_DrawPixel(29, 11, 255, 150, 0);
                matrix_DrawPixel(30, 10, 255, 150, 0);
            }
            else
            {
                set_ButtonState(1,0);
                matrix_DrawPixel(29, 9, 40, 25, 0);
                matrix_DrawPixel(29, 11, 40, 25, 0);
                matrix_DrawPixel(30, 10, 40, 25, 0);
            }

            // Up or X
            if ( (controller_data & 0x04) || (controller_data & 0x40) )
            {
                button_state = get_ButtonState(2);
                if(button_state < 2)
                {
                  set_ButtonState(2, button_state+1);
                }
                matrix_DrawPixel(28, 5, 0, 0, 255);
                matrix_DrawPixel(29, 4, 0, 0, 255);
                matrix_DrawPixel(29, 6, 0, 0, 255);
            }
            else
            {
                set_ButtonState(2,0);
                matrix_DrawPixel(28, 5, 0, 0, 25);
                matrix_DrawPixel(29, 4, 0, 0, 25);
                matrix_DrawPixel(29, 6, 0, 0, 25);
            }

            // Right or A
            if ( (controller_data & 0x08) || (controller_data & 0x80) )
            {
                button_state = get_ButtonState(3);
                if(button_state < 2)
                {
                  set_ButtonState(3, button_state+1);
                }
                matrix_DrawPixel(28, 1, 255, 0, 0);
                matrix_DrawPixel(29, 0, 255, 0, 0);
                matrix_DrawPixel(30, 1, 255, 0, 0);
            }
            else
            {
                set_ButtonState(3,0);
                matrix_DrawPixel(28, 1, 25, 0, 0);
                matrix_DrawPixel(29, 0, 25, 0, 0);
                matrix_DrawPixel(30, 1, 25, 0, 0);
            }
            break;
    }
    
    return state;
}

int (*button_GetTick())(int) { return Tick_Button; }