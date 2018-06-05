#include "../header/inputSM.h"
#include "../header/uart.h"

#include "../header/LinkedList.h"

#include "../header/globals.h"

enum input_States {input_Start, input_Update};
int Tick_Input(int state)
{
    unsigned char rx[2];
    
    switch(state) // Transitions
    {
        case input_Start:
            state = input_Update;
            break;
        case input_Update:
            state = input_Update;
            break;
        default:
            state = input_Start;
    }
    
    switch(state) // Actions
    {
        case input_Start:
            break;
        case input_Update:
            while(UART_available())
            {
                UART_Read(rx,2);
                switch(rx[0])
                {
                    case 0x01: // Button Data
                        set_ControllerData(rx[1]);
                        break;
                    case 0x02: // Map Data
                        mapList.add(rx[1]);
                        break;
                    case 0x03: // Enable Data
                        set_PlayEnable(rx[1]);
                        break;
                    case 0x04: // Tempo
                        set_Tempo(rx[1]);
                    default: break;
                }
            }
            break;
    }
    
    return state;
}

int (*input_GetTick())(int) { return Tick_Input; }