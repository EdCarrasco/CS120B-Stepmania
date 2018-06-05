#include "../header/listSM.h"
#include "../header/matrix.h"

#include "../header/globals.h"

enum list_States {list_Start, list_Off, list_Update};
int Tick_List(int state)
{
    Step *it;
    
    switch(state) // Transitions
    {
        case list_Start:
            state = list_Off;
            break;
        case list_Off:
            if(get_PlayEnable())
            {
                state = list_Update;
            }
            else
            {
                state = list_Off;
            }
            break;
        case list_Update:
            if(get_PlayEnable())
            {
                state = list_Update;
            }
            else
            {
                
                while(stepList.size() > 0)
                {
                    Step *del = stepList.pop();
                    delete del;
                }
                
                stepList.clear();
                state = list_Off;
            }
            break;
        default:
            state = list_Start;
    }
    
    switch(state) // Actions
    {
        case list_Start:
            break;
        case list_Off:
            break;
        case list_Update:
            unsigned char i = 0;
            it = stepList.get(0);
            while(it != NULL)
            {
                it->Update();
                if(it->getX() >= 28)
                {
                  it = stepList.get(i+1);
                  Step *del = stepList.remove(i);
                  delete del;
                }
                else
                {
                  i++;
                  it = stepList.get(i);
                }
            }
            break;
    }
    
    return state;
}

int (*list_GetTick())(int) { return Tick_List; }