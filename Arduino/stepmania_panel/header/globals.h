#ifndef __globals_h__
#define __globals_h__

#include "LinkedList.h"
#include "steps.h"

extern unsigned char program_period;
void set_ProgramPeriod(unsigned char period);
unsigned char get_ProgramPeriod(void);

extern unsigned char input_period;
void set_InputPeriod(unsigned char period);
unsigned char get_InputPeriod(void);

extern unsigned char button_period;
void set_ButtonPeriod(unsigned char period);
unsigned char get_ButtonPeriod(void);

extern unsigned char step_period;
void set_StepPeriod(unsigned char period);
unsigned char get_StepPeriod(void);

extern unsigned char list_period;
void set_ListPeriod(unsigned char period);
unsigned char get_ListPeriod(void);

extern unsigned char controller_data;
void set_ControllerData(unsigned char data);
unsigned char get_ControllerData(void);

extern unsigned char button_states[4];
void set_ButtonState(unsigned char index, unsigned char state);
unsigned char get_ButtonState(unsigned char index);

extern unsigned char map_data;
void set_MapData(unsigned char data);
unsigned char get_MapData(void);

extern LinkedList<unsigned char> mapList;
extern LinkedList<Step*> stepList;

extern unsigned char play_enable;
void set_PlayEnable(unsigned char data);
unsigned char get_PlayEnable(void);

extern unsigned char tempo;
void set_Tempo(unsigned char data);
unsigned char get_Tempo(void);


#endif