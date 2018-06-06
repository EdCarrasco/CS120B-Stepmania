void set_ControllerData(unsigned short data);
unsigned short get_ControllerData();

void set_ProgramPeriod(unsigned long period);
unsigned long get_ProgramPeriod();

void set_ControllerPeriod(unsigned long period);
unsigned long get_ControllerPeriod();

void set_LCDPeriod(unsigned long period);
unsigned long get_LCDPeriod();

void set_MusicPeriod(unsigned long period);
unsigned long get_MusicPeriod();

void set_USARTPeriod(unsigned long period);
unsigned long get_USARTPeriod();

void set_PlayEnable(unsigned char enable);
unsigned long get_PlayEnable();

void set_GameMap(unsigned char *stepmap);
unsigned char* get_GameMap();

void set_GameMapSize(unsigned short map_size);
unsigned short get_GameMapSize();

void set_Tempo(unsigned char tempo);
unsigned short get_Tempo();

void set_Combo(unsigned char in_combo);
unsigned char get_Combo();

void set_Hits(unsigned char in_hits);
unsigned char get_Hits();

void set_Max_Hits_Prom(unsigned char score);
unsigned char get_Max_Hits_Prom();
void set_Max_Hits(unsigned char score);
unsigned char get_Max_Hits();

void set_Max_Combo_Prom(unsigned char score);
unsigned char get_Max_Combo_Prom();
void set_Max_Combo(unsigned char score);
unsigned char get_Max_Combo();