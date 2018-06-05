#include "globals.h"
#include "eeprom.h"

unsigned short controller_data;
// SNES Controller Data Format: 0-15
// B, Y, SELECT, START, UP, DOWN, LEFT, RIGHT, A, X, L, R, 1, 1, 1, 1
void set_ControllerData(unsigned short data) { controller_data = data; }
unsigned short get_ControllerData() { return controller_data; }

unsigned long program_period;
void set_ProgramPeriod(unsigned long period) { program_period = period; }
unsigned long get_ProgramPeriod() { return program_period; }

unsigned long controller_period;
void set_ControllerPeriod(unsigned long period) { controller_period = period; }
unsigned long get_ControllerPeriod() { return controller_period; }

unsigned long LCD_period;
void set_LCDPeriod(unsigned long period) { LCD_period = period; }
unsigned long get_LCDPeriod() { return LCD_period; }

unsigned long music_period;
void set_MusicPeriod(unsigned long period) { music_period = period; }
unsigned long get_MusicPeriod() { return music_period; }
	
unsigned long usart_period;
void set_USARTPeriod(unsigned long period) { usart_period = period; }
unsigned long get_USARTPeriod() { return usart_period; }

unsigned char play_enable;
void set_PlayEnable(unsigned char enable) { play_enable = enable; }
unsigned long get_PlayEnable() { return play_enable; }
	
unsigned char* game_map;
void set_GameMap(unsigned char *stepmap) {game_map = stepmap; };
unsigned char* get_GameMap() { return game_map; }

unsigned short game_map_size;
void set_GameMapSize(unsigned short map_size) { game_map_size = map_size; }
unsigned short get_GameMapSize() { return game_map_size; }

unsigned short tempo;
void set_Tempo(unsigned char in_tempo) { tempo = in_tempo; }
unsigned short get_Tempo() { return tempo; }

unsigned char max_combo;
void set_Max_Combo_Prom()
{
	EEPROM_Write(0,max_combo);
}
unsigned char get_Max_Combo_Prom()
{
	return EEPROM_Read(0);
}
void set_Max_Combo(unsigned char score)
{
	if(score > max_combo)
	{
		max_combo = score;
	}
}
unsigned char get_Max_Combo()
{
	return max_combo;
}

void reset_Max_Combo()
{
	max_combo = 0;
	set_Max_Combo_Prom(0,0);
}