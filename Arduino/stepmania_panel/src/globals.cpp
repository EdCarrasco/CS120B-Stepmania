#include "../header/globals.h"

unsigned char program_period;
void set_ProgramPeriod(unsigned char period) { program_period = period; }
unsigned char get_ProgramPeriod(void) { return program_period; }

unsigned char input_period;
void set_InputPeriod(unsigned char period) { input_period = period; }
unsigned char get_InputPeriod(void) { return input_period; }

unsigned char button_period;
void set_ButtonPeriod(unsigned char period) { button_period = period; }
unsigned char get_ButtonPeriod(void) { return button_period; }

unsigned char step_period;
void set_StepPeriod(unsigned char period) { step_period = period; }
unsigned char get_StepPeriod(void) { return step_period; }

unsigned char list_period;
void set_ListPeriod(unsigned char period) { list_period = period; }
unsigned char get_ListPeriod(void) { return step_period; }

unsigned char controller_data;
void set_ControllerData(unsigned char data) { controller_data = data; }
unsigned char get_ControllerData(void) { return controller_data; }

unsigned char button_states[4];
void set_ButtonState(unsigned char index, unsigned char state) { button_states[index] = state; }
unsigned char get_ButtonState(unsigned char index) { return button_states[index]; }

unsigned char map_data;
void set_MapData(unsigned char data) { map_data = data; }
unsigned char get_MapData(void) { return map_data; }

LinkedList<unsigned char> mapList;
LinkedList<Step*> stepList;

unsigned char play_enable;
void set_PlayEnable(unsigned char data) { play_enable = data; }
unsigned char get_PlayEnable(void) { return play_enable; }

unsigned char tempo;
void set_Tempo(unsigned char data) { tempo = data; }
unsigned char get_Tempo(void) { return tempo; }