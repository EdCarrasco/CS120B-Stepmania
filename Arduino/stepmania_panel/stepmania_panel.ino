#include "header/test.h"
#include "header/steps.h"
#include "header/uart.h"
#include "header/matrix.h"

#include "header/globals.h"

#include "header/LinkedList.h"

#include "header/inputSM.h"
#include "header/buttonSM.h"
#include "header/stepSM.h"
#include "header/listSM.h"

typedef struct _task {
    /*Tasks should have members that include: state, period,
        a measurement of elapsed time, and a function pointer.*/
    signed char state; //Task's current state
    unsigned long period; //Task period
    unsigned long elapsed_time; //Time elapsed since last task tick
    int (*TickFunction)(int); //Task tick function
} Task;


static Task inputTask, buttonTask, stepTask, listTask;
static Task *tasks[] = { &inputTask, &buttonTask, &stepTask, &listTask };

//StepFactory stepFactory;
//LinkedList<Step*> stepList = LinkedList<Step*>();

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
    unsigned long input_period = 10;
    unsigned long button_period = 10;
    unsigned long step_period = 1;
    unsigned long list_period = 5;
    
    set_InputPeriod(input_period);
    set_ButtonPeriod(button_period);
    set_StepPeriod(step_period);
    set_ListPeriod(list_period);
    
    unsigned long gcd = findGCD(input_period, button_period);
    gcd = findGCD(gcd, step_period);
    gcd = findGCD(gcd, list_period);
  
    set_ProgramPeriod(gcd);
    
    unsigned char i = 0;
    tasks[i]->state = 0;
    tasks[i]->period = input_period/gcd;
    tasks[i]->elapsed_time = tasks[i]->period;
    tasks[i]->TickFunction = input_GetTick();
    i++;
    tasks[i]->state = 0;
    tasks[i]->period = button_period/gcd;
    tasks[i]->elapsed_time = tasks[i]->period;
    tasks[i]->TickFunction = button_GetTick();
    i++;
    tasks[i]->state = 0;
    tasks[i]->period = step_period/gcd;
    tasks[i]->elapsed_time = tasks[i]->period;
    tasks[i]->TickFunction = step_GetTick();
    i++;
    tasks[i]->state = 0;
    tasks[i]->period = list_period/gcd;
    tasks[i]->elapsed_time = tasks[i]->period;
    tasks[i]->TickFunction = list_GetTick();
    
}

void setup() {
  init_Tasks();
  UART_init();
  matrix_init();
}

void runTicks()
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

void loop() {
  runTicks();
  delay(get_ProgramPeriod());
}
