extern unsigned short controller_data;
void set_ControllerData(unsigned short data);
unsigned short get_ControllerData();

extern unsigned long program_period;
void set_ProgramPeriod(unsigned long period);
unsigned long get_ProgramPeriod();

extern unsigned long controller_period_;
void set_ControllerPeriod(unsigned long period);
unsigned long get_ControllerPeriod();

extern unsigned long LCD_period;
void set_LCDPeriod(unsigned long period);
unsigned long get_LCDPeriod();

extern unsigned long music_period;
void set_MusicPeriod(unsigned long period);
unsigned long get_MusicPeriod();

extern unsigned char max_combo;
void set_Max_Combo_Prom();
unsigned char get_Max_Combo_Prom();
void set_Max_Combo(unsigned char score);
unsigned char get_Max_Combo();
void reset_Max_Combo();