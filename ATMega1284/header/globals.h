unsigned short controller_data;
void set_ControllerData(unsigned short data);
unsigned short get_ControllerData();

unsigned long program_period;
void set_ProgramPeriod(unsigned long period);
unsigned long get_ProgramPeriod();

unsigned long controller_period_;
void set_ControllerPeriod(unsigned long period);
unsigned long get_ControllerPeriod();

unsigned long LCD_period;
void set_LCDPeriod(unsigned long period);
unsigned long get_LCDPeriod();

unsigned long music_period;
void set_MusicPeriod(unsigned long period);
unsigned long get_MusicPeriod();

unsigned long usart_period;
void set_USARTPeriod(unsigned long period);
unsigned long get_USARTPeriod();

unsigned char play_enable;
void set_PlayEnable(unsigned char enable);
unsigned long get_PlayEnable();

unsigned char* game_map;
void set_GameMap(unsigned char *stepmap);
unsigned char* get_GameMap();

unsigned short game_map_size;
void set_GameMapSize(unsigned short map_size);
unsigned short get_GameMapSize();

unsigned short tempo;
void set_Tempo(unsigned char tempo);
unsigned short get_Tempo();

unsigned char combo;
void set_Combo(unsigned char in_combo);
unsigned char get_Combo();

unsigned char hits;
void set_Hits(unsigned char in_hits);
unsigned char get_Hits();

unsigned char max_hits;
void set_Max_Hits_Prom(unsigned char score);
unsigned char get_Max_Hits_Prom();
void set_Max_Hits(unsigned char score);
unsigned char get_Max_Hits();

unsigned char max_combo;
void set_Max_Combo_Prom(unsigned char score);
unsigned char get_Max_Combo_Prom();
void set_Max_Combo(unsigned char score);
unsigned char get_Max_Combo();