#include "../header/stepSM.h"
#include "../header/steps.h"

#include "../header/LinkedList.h"

#include "../header/globals.h"

enum step_States {step_Start, step_Off, step_Update};
int Tick_Step(int state)
{   
    static unsigned char tempo;
    static unsigned char tempo_time;
    static unsigned char beat;
    
    switch(state) // Transitions
    {
        case step_Start:
            state = step_Off;
            tempo_time = 0;
            beat = 0;
            break;
        case step_Off:
            if(get_PlayEnable())
            {
                tempo = 92; //get_Tempo();
                tempo_time = tempo;
                state = step_Update;
            }
            else
            {
                state = step_Off;
            }
            break;
        case step_Update:
            if(get_PlayEnable())
            {
                tempo_time += get_StepPeriod();
                state = step_Update;
            }
            else
            {
                beat = 0;
                mapList.clear();
                state = step_Off;
            }
            break;
        default:
            state = step_Start;
    }
    
    switch(state) // Actions
    {
        case step_Start:
            break;
        case step_Off:
            tempo = 0;
            tempo_time = 0;
            beat = 0;
            break;
        case step_Update:
            if(tempo_time >= tempo)
            {   
                tempo = (tempo == 92) ? 93 : 92;
                
                tempo_time = 0;
                make_Steps(mapList.remove(0),beat,stepList);
                beat++;
                if(beat >= 4)
                {
                    beat = 0;
                }
            }
            break;
    }
    
    return state;
}

int (*step_GetTick())(int) { return Tick_Step; }