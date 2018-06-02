#include "gameSM.h"
#include "tabula.h"

#include "globals.h"

// SNES Controller Data Format: 0-15
// B, Y, SELECT, START, UP, DOWN, LEFT, RIGHT, A, X, L, R, 0, 0, 0, 0
#define START ((get_ControllerData() & 0x0008) && 0x0008)
#define SELECT ((get_ControllerData() & 0x0004) && 0x0004)
#define B ((get_ControllerData() & 0x0001) && 0x0001)
#define Y ((get_ControllerData() & 0x0002) && 0x0002)
#define A ((get_ControllerData() & 0x0100) && 0x0100)
#define X ((get_ControllerData() & 0x2000) && 0x0200)

#define LEFT 3
#define DOWN 2
#define UP 1
#define RIGHT 0

enum Game_States {game_Start, game_Off, game_Update};
int Tick_Game(int state)
{
    static unsigned char combo;
    static unsigned char max_combo;
    
    static unsigned char button_stream;
    
    static unsigned char beat_stream;
    
    static unsigned char beats[4];
    static unsigned char hits[4];
    
    static unsigned char map_size;
    static unsigned char map_index;
    
    switch(state) // Transitions
    {
        case game_Start:
            combo = 0;
            max_combo = 0;
            button_stream = 0x00;
            beat_stream = 0x00;
            map_size = 0;
            map_index = 0;
            state = game_Off;
            break;
        case game_Off:
            if(START)
            {
                map_size = get_Tabula_Map_Size();
                state = game_Update;
            }
            else
            {
                state = game_Off;
            }
            break;
        case game_Update:
            if(SELECT || map_index > map_size)
            {
                state = game_Off;
            }
            else
            {
                state = game_Update;
            }
            break;
        default:
            state = game_Start;
            break;
    }
    
    switch(state) // Actions
    {
        case game_Start: break;
        case game_Off:
            combo = 0;
            max_combo = 0;
            button_stream = 0x00;
            beat_stream = 0x00;
            map_size = 0;
            map_index = 0; 
            break;
        case game_Update:
            if(map_index <= map_size)
            {
                button_stream = (button_stream<<4);
                button_stream |= (B<<LEFT) | (Y<<DOWN) | (X<<UP) | (A<<RIGHT);
                beat_stream = get_Tabula_Map(map_index);
                beats[3] = ((beat_stream>>6) & 0x03);
                beats[2] = ((beat_stream>>4) & 0x03);
                beats[1] = ((beat_stream>>2) & 0x03);
                beats[0] = ((beat_stream) & 0x03);
                
                for(unsigned char i = 0; i < 4; i++)
                {
                    if(beats[i] == 0x00)
                    {
                        hits[i] = 0;
                    }
                    else if(beats[i] == 0x01)
                    {
                        if( !((button_stream>>(i+4)) & 0x01) && !((button_stream>>i) & 0x01) ) { }
                        else if( !((button_stream>>(i+4)) & 0x01) && ((button_stream>>i) & 0x01) )
                        {
                            hits[i] = 0;
                        }
                        else if( ((button_stream>>(i+4)) & 0x01) && !((button_stream>>i) & 0x01) ) { }
                        else if( ((button_stream>>(i+4)) & 0x01) && ((button_stream>>i) & 0x01) ) { }
                    }
                    else if(beats[i] == 0x02)
                    {
                        if( !((button_stream>>(i+4)) & 0x01) && !((button_stream>>i) & 0x01) ) { }
                        else if( !((button_stream>>(i+4)) & 0x01) && ((button_stream>>i) & 0x01) )
                        {
                            if(hits[i] == 1)
                            {
                                hits[i] = 0;
                            }
                        }
                        else if( ((button_stream>>(i+4)) & 0x01) && !((button_stream>>i) & 0x01) )
                        {
                            if(hits[i] == 0)
                            {
                                hits[i] = 2;
                            }
                        }
                        else if( ((button_stream>>(i+4)) & 0x01) && ((button_stream>>i) & 0x01) ) { }
                    }
                    else if(beats[i] == 0x03)
                    {
                        if( !((button_stream>>(i+4)) & 0x01) && !((button_stream>>i) & 0x01) )
                        {
                            if(hits[i] == 0)
                            {
                                hits[i] = 2;
                            }
                        }
                        else if( !((button_stream>>(i+4)) & 0x01) && ((button_stream>>i) & 0x01) )
                        {
                            if(hits[i] == 0)
                            {
                                hits[i] = 2;
                            }
                        }
                        else if( ((button_stream>>(i+4)) & 0x01) && !((button_stream>>i) & 0x01) )
                        {
                            if(hits[i] == 0)
                            {
                                hits[i] = 2;
                            }
                        }
                        else if( ((button_stream>>(i+4)) & 0x01) && ((button_stream>>i) & 0x01) )
                        {
                            hits[i] = 0;
                        }
                    }
                }
                
                if(combo > max_combo)
                {
                    max_combo++;
                }
                map_index++;
            }
            break;
    }
    
    return state;
}

int (*game_GetTick())(int){ return Tick_Game; }