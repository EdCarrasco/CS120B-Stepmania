#include "usartSM.h"
#include "usart.h"

#include "globals.h"

// SNES Controller Data Format: 0-15
// B, Y, SELECT, START, UP, DOWN, LEFT, RIGHT, A, X, L, R, 0, 0, 0, 0

enum Music_States {usart_Start, usart_Off, usart_Update};
int Tick_USART(int state)
{    
	static unsigned char *stepmap;
	static unsigned short map_index;
	static unsigned short map_size;
	static unsigned char count;
	static unsigned char combo;
	static unsigned char max_combo;
	static unsigned char hits;
	
    switch(state) // Transitions
    {
		case usart_Start:
			count = 0;
			map_index = 0;
			map_size = 0;

			combo = 0;
			max_combo = 0;
			hits = 0;
			state = usart_Off;
			break;
		case usart_Off:
			if(get_PlayEnable())
			{
				count = get_Tempo();
				map_index = 0;
				stepmap = get_GameMap();
				map_size = get_GameMapSize();
				for(unsigned char i = 0; i < 8; i++)
				{
					USART_Send(0x02,*stepmap);
					stepmap++;
					map_index++;
				}
				USART_Send(0x03,0x01);
				USART_Send(0x04,get_Tempo());

				combo = 0;
				set_Combo(combo);
				hits = 0;
				set_Hits(hits);
				state = usart_Update;
			}
			else
			{
				USART_Send(0x03,0x00);
				state = usart_Off;
			}
		case usart_Update:
			if(get_PlayEnable())
			{
				state = usart_Update;
			}
			else
			{
				USART_Send(0x03,0x00);
				if(max_combo > get_Max_Combo())
				{
					set_Max_Combo(max_combo);
					set_Max_Combo_Prom(max_combo);
				}
				if(hits > get_Max_Hits())
				{
					set_Max_Hits(hits);
					set_Max_Hits_Prom(hits);
				}
				state = usart_Off;
			}
			break;
		default:
			state = usart_Start;
			break;
    }
    
    switch(state) // Actions
    {
		case usart_Start: break;
		case usart_Off:
			send_Controller();
			break;
		case usart_Update:
			send_Controller();
			
			if(count >= (get_Tempo()) && map_index < map_size)
			{
				USART_Send(0x02,*stepmap);
				stepmap++;
				count = 0;
				map_index++;
			}
			count += get_USARTPeriod();
			
			while(USART_HasReceived())
			{
				unsigned char data = USART_Receive();
				if(data == 0x02)
				{
					hits++;
					set_Hits(hits);
					combo++;
					set_Combo(combo);
					if(combo > max_combo)
					{
						max_combo = combo;
					}
				}
				else if (data == 0x01)
				{
					combo = 0;
					set_Combo(combo);
				}
			}
			
			break;
    }
    
    return state;
}
    
int (*usart_GetTick())(int){ return Tick_USART; }

void send_Controller()
{
	unsigned short controller_data = get_ControllerData();
	
	//0bRUDLAXBY
	USART_Send(0x01,  ((char)(
	(controller_data & 0b000000000000010)>>1 | // Y
	(controller_data & 0b000000000000001)<<1 | // B
	(controller_data & 0b000001000000000)>>7 | // X
	(controller_data & 0b000000100000000)>>5 | // A
	
	(controller_data & 0b000000001000000)>>2 | // Left
	(controller_data & 0b000000000100000) |    // Down
	(controller_data & 0b000000000010000)<<2 | // Up
	(controller_data & 0b000000010000000) ) ) ); // Right
}