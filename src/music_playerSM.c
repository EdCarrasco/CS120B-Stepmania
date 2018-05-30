#include "music_playerSM.h"
#include "pwm.h"
#include "tabula.h"

#include "globals.h"

// SNES Controller Data Format: 0-15
// B, Y, SELECT, START, UP, DOWN, LEFT, RIGHT, A, X, L, R, 0, 0, 0, 0
#define START (get_ControllerData() & 0x0008)
#define SELECT (get_ControllerData() & 0x0004)

#define music_tracks 3

enum Music_States {music_Start, music_Off, music_Update};
int Tick_Music(int state)
{    
	static unsigned char play_enable;
	
    static unsigned char note_index[music_tracks];
    static unsigned char note_size[music_tracks];
    static unsigned long note_duration[music_tracks];
    static unsigned long elapsed_time[music_tracks];
    
    switch(state) // Transitions
    {
        case music_Start:
			play_enable = 0;
            for(unsigned char i = 0; i < music_tracks; i++)
            {
                note_index[i] = 0;
                note_size[i] = 0;
                note_duration[i] = 0;
                elapsed_time[i] = 0;
                set_PWM(i,0);
            }
            state = music_Off;
            break;
        case music_Off:
			play_enable = START;
            if(play_enable)
            {
                for(unsigned char i = 0; i < music_tracks; i++)
                {
                    note_size[i] = get_Tabula_Size(i);
                }
                state = music_Update;
            }
            else
            {
                state = music_Off;
            }
            break;
        case music_Update:
            if( (!play_enable) | SELECT)
            {
                state = music_Off;
            }
            else
            {
                for(unsigned char i = 0; i < music_tracks; i++)
                {
                    if(elapsed_time[i] >= note_duration[i] && note_index[i] < note_size[i])
                    {
                        elapsed_time[i] = 0;
                        note_index[i]++;
                        note_duration[i] = get_Tabula_Duration(i,note_index[i]);
                        set_PWM(i,get_Tabula_Tone(i,note_index[i]));
                    }
                }
                state = music_Update;
                for(unsigned char i = 0; i < music_tracks; i++)
                {
                    if(note_index[i] >= note_size[i])
                    {
                        state = music_Off;
                    }
                }
            }
            break;
        default:
            state = music_Start;
            break;
    }
    
    switch(state) // Actions
    {
        case music_Start: break;
        case music_Off:
            play_enable = 0;
            for(unsigned char i = 0; i < music_tracks; i++)
            {
                note_index[i] = 0;
                note_size[i] = 0;
                note_duration[i] = 0;
                elapsed_time[i] = 0;
                set_PWM(i,0);
            }
            break;
        case music_Update:
            for(unsigned char i = 0; i < music_tracks; i++)
            {
                elapsed_time[i] += get_MusicPeriod();
            }
            break;
    }
    
    return state;
}
    
int (*music_GetTick())(int){ return Tick_Music; }