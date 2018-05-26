#include "controllerSM.h"
#include "snes.h"

#include "globals.h"

enum Controller_States {controller_Start, controller_Update};
int Tick_Controller(int state)
{
    switch(state) // Transitions
    {
        case controller_Start:
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
            set_ControllerData(snes_GetData());
            break;
    }
    
    return state;
}

int (*controller_GetTick())(int) { return Tick_Controller; }