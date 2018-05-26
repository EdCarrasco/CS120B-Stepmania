/*
 * stepmania.c
 *
 * Created: 2018-05-25 15:25:30
 *  Author: JonathanOaks
 */ 

#define F_CPU 8000000UL // Clock Definition 8MHz

#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "lcd_4bit.h"
#include "timer.h"

#include "globals.h"

#include "controllerSM.h"
#include "lcdSM.h"

typedef struct _task {
    /*Tasks should have members that include: state, period,
        a measurement of elapsed time, and a function pointer.*/
    signed char state; //Task's current state
    unsigned long period; //Task period
    unsigned long elapsed_time; //Time elapsed since last task tick
    int (*TickFunction)(int); //Task tick function
} Task;

static Task controllerTask, lcdTask;
static Task *tasks[] = { &controllerTask, &lcdTask };

static unsigned long program_period;
static unsigned long period_Controller = 25;
static unsigned long period_LCD = 100;

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
    program_period = findGCD(period_Controller, period_Controller);
    program_period = findGCD(period_Controller, period_LCD);
    
    unsigned char i = 0;
    tasks[i]->state = 0;
    tasks[i]->period = period_Controller/program_period;
    tasks[i]->elapsed_time = tasks[i]->period;
    tasks[i]->TickFunction = controller_GetTick();
    i++;
    tasks[i]->state = 0;
    tasks[i]->period = period_LCD/program_period;
    tasks[i]->elapsed_time = tasks[i]->period;
    tasks[i]->TickFunction = lcd_GetTick();
    
}

int main(void)
{
    DDRA = 0xFE; PORTA = 0x01;
    DDRC = 0xFF; PORTC = 0x00;
    
    LCD_init();
    init_Tasks();
    
    TimerSet(program_period);
    TimerOn();
    
    set_sleep_mode(3);
    while(1) { sleep_enable(); }
    
    return 0;
}