#include "controllerSM.h"
#include "snes.h"
#include "usart.h"

#include "globals.h"

// SNES Controller Data Format: 0-15
// B, Y, SELECT, START, UP, DOWN, LEFT, RIGHT, A, X, L, R, 0, 0, 0, 0

enum Controller_States {controller_Start, controller_Update};
int Tick_Controller(int state)
{
	static unsigned char combo;
	static unsigned char max_combo;
	static unsigned short data;
    switch(state) // Transitions
    {
        case controller_Start:
			combo = 0;
			data = 0;
			max_combo = get_Max_Combo();
            controller_data = 0x0000;
            state = controller_Update;
            break;
        case controller_Update:
            state = controller_Update;
            break;
        default:
            state = controller_Start;
            break;
    }
    
    switch(state) // Actions
    {
        case controller_Start: break;
        case controller_Update:
			data = snes_GetData();
            
            //YBXALDUR
            USART_Send( ((char)( 
                (data & 0b000000000000010)>>1 | // Y
                (data & 0b000000000000001)<<1 | // B
                (data & 0b000001000000000)>>7 | // X
                (data & 0b000000100000000)>>5 | // A
                
                (data & 0b000000001000000)>>2 | // Left
                (data & 0b000000000100000) |    // Down
                (data & 0b000000000010000)<<2 | // Up
                (data & 0b000000010000000) ) ) ); // Right
            
            set_ControllerData(data);
			
            
			if( (data & 0x0001) )
			{
				combo++;
				if(combo > max_combo)
				{
					max_combo = combo;
					set_Max_Combo(max_combo);
					set_Max_Combo_Prom();
				}
			}
			if (data & 0x0010)
			{
				max_combo = 0;
				reset_Max_Combo();
			}
			
            break;
    }
    
    return state;
}

int (*controller_GetTick())(int) { return Tick_Controller; }