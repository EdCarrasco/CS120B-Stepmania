#include "controllerSM.h"
#include "snes.h"

#include "globals.h"

// SNES Controller Data Format: 0-15
// B, Y, SELECT, START, UP, DOWN, LEFT, RIGHT, A, X, L, R, 0, 0, 0, 0

enum Controller_States {controller_Start, controller_Update};
int Tick_Controller(int state)
{
	unsigned short data;
    switch(state) // Transitions
    {
        case controller_Start:
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
            set_ControllerData(data);
			
			if( (get_ControllerData() & 0x0400) && (get_ControllerData() & 0x0800) ) // L and R
			{

				set_Max_Combo(0);
				if(get_Max_Combo_Prom() > 0)
				{
					set_Max_Combo_Prom(0);
				}

				set_Max_Hits(0);
				if(get_Max_Hits_Prom() > 0)
				{
					set_Max_Hits_Prom(0);
				}
			}
			
			if(data & 0x0004) // SELECT
			{
				set_PlayEnable(0);
			}
			else if(data & 0x0008) // START
			{
				set_PlayEnable(1);
			}
            break;
    }
    
    return state;
}

int (*controller_GetTick())(int) { return Tick_Controller; }