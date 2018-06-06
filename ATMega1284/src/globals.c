#include "globals.h"
#include "eeprom.h"

unsigned short controller_data = 0;
// SNES Controller Data Format: 0-15
// B, Y, SELECT, START, UP, DOWN, LEFT, RIGHT, A, X, L, R, 1, 1, 1, 1
void set_ControllerData(unsigned short data) { controller_data = data; }
unsigned short get_ControllerData() { return controller_data; }

unsigned long program_period = 0;
void set_ProgramPeriod(unsigned long period) { program_period = period; }
unsigned long get_ProgramPeriod() { return program_period; }

unsigned long controller_period = 0;
void set_ControllerPeriod(unsigned long period) { controller_period = period; }
unsigned long get_ControllerPeriod() { return controller_period; }

unsigned long LCD_period = 0;
void set_LCDPeriod(unsigned long period) { LCD_period = period; }
unsigned long get_LCDPeriod() { return LCD_period; }

unsigned long music_period = 0;
void set_MusicPeriod(unsigned long period) { music_period = period; }
unsigned long get_MusicPeriod() { return music_period; }
	
unsigned long usart_period = 0;
void set_USARTPeriod(unsigned long period) { usart_period = period; }
unsigned long get_USARTPeriod() { return usart_period; }

unsigned char play_enable = 0;
void set_PlayEnable(unsigned char enable) { play_enable = enable; }
unsigned long get_PlayEnable() { return play_enable; }
	
unsigned char* game_map = 0;
void set_GameMap(unsigned char *stepmap) {game_map = stepmap; };
unsigned char* get_GameMap() { return game_map; }

unsigned short game_map_size = 0;
void set_GameMapSize(unsigned short map_size) { game_map_size = map_size; }
unsigned short get_GameMapSize() { return game_map_size; }

unsigned short tempo = 0;
void set_Tempo(unsigned char in_tempo) { tempo = in_tempo; }
unsigned short get_Tempo() { return tempo; }

unsigned char combo = 0;
void set_Combo(unsigned char in_combo) { combo = in_combo; }
unsigned char get_Combo() { return combo; }

unsigned char hits = 0;
void set_Hits(unsigned char in_hits) { hits = in_hits; }
unsigned char get_Hits() { return hits; }

unsigned char max_hits = 0;
void set_Max_Hits_Prom(unsigned char score) { EEPROM_Write(0x01,score); }
unsigned char get_Max_Hits_Prom() { return EEPROM_Read(&0x01); }
void set_Max_Hits(unsigned char score) { max_hits = score; }
unsigned char get_Max_Hits() { return max_hits; }

unsigned char max_combo = 0;
void set_Max_Combo_Prom(unsigned char score) { EEPROM_Write(0x00,score); }
unsigned char get_Max_Combo_Prom() { return EEPROM_Read(0x00); }
void set_Max_Combo(unsigned char score) { max_combo = score; }
unsigned char get_Max_Combo() { return max_combo; }