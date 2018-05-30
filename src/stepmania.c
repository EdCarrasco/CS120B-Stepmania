/*
 * stepmania.c
 *
 * Created: 2018-05-25 15:25:30
 *  Author: JonathanOaks
 */ 

#include <avr/io.h>
#include <avr/sleep.h>
#include "lcd_4bit.h"
#include "timer.h"

#include "globals.h"

#include "controllerSM.h"
#include "lcdSM.h"
#include "music_playerSM.h"

typedef struct _task {
    /*Tasks should have members that include: state, period,
        a measurement of elapsed time, and a function pointer.*/
    signed char state; //Task's current state
    unsigned long period; //Task period
    unsigned long elapsed_time; //Time elapsed since last task tick
    int (*TickFunction)(int); //Task tick function
} Task;

static Task controllerTask, lcdTask, musicTask;
static Task *tasks[] = { &controllerTask, &lcdTask, &musicTask };

void TimerISR()
{
    for(unsigned char i = 0; i < sizeof tasks / sizeof *tasks; i++)
    {
        if(tasks[i]->elapsed_time >= tasks[i]->period)
        {
            tasks[i]->state = tasks[i]->TickFunction(tasks[i]->state);
            tasks[i]->elapsed_time = 0;
        }
        tasks[i]->elapsed_time += 1;
    }
}

unsigned long int findGCD(unsigned long a, unsigned long b)
{
    unsigned long c;
    while(1){
        c = a%b;
        if(c==0){return b;}
        a = b;
        b = c;
    }
    return 0;
}

void init_Tasks()
{
    unsigned long controller_period = 50;
    unsigned long LCD_period = 25;
    unsigned long music_period = 10;
    
    set_ControllerPeriod(controller_period);
    set_LCDPeriod(LCD_period);
    set_MusicPeriod(music_period);
    
    unsigned long gcd = findGCD(controller_period, LCD_period);
    gcd = findGCD(gcd, music_period);
	
    set_ProgramPeriod(gcd);
    
    unsigned char i = 0;
    tasks[i]->state = 0;
    tasks[i]->period = controller_period/gcd;
    tasks[i]->elapsed_time = tasks[i]->period;
    tasks[i]->TickFunction = controller_GetTick();
    i++;
    tasks[i]->state = 0;
    tasks[i]->period = LCD_period/gcd;
    tasks[i]->elapsed_time = tasks[i]->period;
    tasks[i]->TickFunction = lcd_GetTick();
    i++;
    tasks[i]->state = 0;
    tasks[i]->period = music_period/gcd;
    tasks[i]->elapsed_time = tasks[i]->period;
    tasks[i]->TickFunction = music_GetTick();
    
}

int main(void)
{
    DDRA = 0xFE; PORTA = 0x01;
	DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    
    LCD_init();
    init_Tasks();
    
    TimerSet(get_ProgramPeriod());
    TimerOn();
    
    set_sleep_mode(3);
    while(1) { sleep_enable(); }
    
    return 0;
}