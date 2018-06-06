#include "music_playerSM.h"
#include "pwm.h"
#include "tabula.h"
#include "usart.h"

#include "globals.h"

#define music_tracks 3

enum Music_States {music_Start, music_Off, music_Wait, music_Update};
int Tick_Music(int state)
{    
    static unsigned char note_index[music_tracks];
    static unsigned char note_size[music_tracks];
    static unsigned long note_duration[music_tracks];
    static unsigned long elapsed_time[music_tracks];
    
    switch(state) // Transitions
    {
        case music_Start:
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
            if(get_PlayEnable())
            {
                for(unsigned char i = 0; i < music_tracks; i++)
                {
					note_index[i] = 0;
                    note_size[i] = get_Tabula_Size(i);
                }
				set_GameMap(get_Tabula_Map());
				set_GameMapSize(get_Tabula_Map_Size());
				set_Tempo(get_Tabula_Tempo());
                state = music_Wait;
            }
            else
            {
                state = music_Off;
            }
            break;
		case music_Wait:
			elapsed_time[0] += get_MusicPeriod();
			if(get_PlayEnable() && elapsed_time[0] >= 750)
			{
				elapsed_time[0] = 0;
				state = music_Update;
			}
			else if (get_PlayEnable() && elapsed_time[0] < 780)
			{
				state = music_Wait;
			}
			else if(!get_PlayEnable())
			{
				state = music_Off;
			}
			break;
        case music_Update:
            if(!get_PlayEnable() || note_index[0] > note_size[0])
            {
				set_PlayEnable(0);
                state = music_Off;
            }
            else
            {
                state = music_Update;
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
				if(elapsed_time[i] >= note_duration[i] && note_index[i] <= note_size[i])
				{
					elapsed_time[i] = 0;
					note_duration[i] = get_Tabula_Duration(i,note_index[i]);
					set_PWM(i,get_Tabula_Tone(i,note_index[i]));
					note_index[i]++;
				}
				elapsed_time[i] += get_MusicPeriod();
			}
            break;
    }
    
    return state;
}
    
int (*music_GetTick())(int){ return Tick_Music; }