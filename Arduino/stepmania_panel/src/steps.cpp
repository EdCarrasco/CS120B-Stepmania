#include "../header/steps.h"
#include "../header/LinkedList.h"
#include "../header/matrix.h"
#include "../header/uart.h"

#include "../header/globals.h"

#define UPDATE_TIME 30

#define LEFT_Y 13
#define DOWN_B 9
#define UP_X 4
#define RIGHT_A 0

//StepHold* last_step[4] = {NULL, NULL, NULL, NULL};

Step::Step(unsigned char Y, unsigned char COLOR[3])
{
    x = 0;
    y = Y;
    r = COLOR[0];
    g = COLOR[1];
    b = COLOR[2];
    
    elapsed_time = UPDATE_TIME;
    hitFlag = false;
}

Step::Step(unsigned char Y, unsigned char R, unsigned char G, unsigned char B)
{
    x = 0;
    y = Y;
    r = R;
    g = G;
    b = B;
    
    elapsed_time = UPDATE_TIME;
}

Step::~Step()
{
    for(unsigned char i = y; i < y+3; i++)
    {
        switch(x)
        {
            case 25:
                matrix_DrawPixel(24, i, 20, 20, 20);
                break;
            case 27:
                matrix_DrawPixel(26, i, 20, 20, 20);
                break;
            default:
                matrix_DrawPixel((x - 1), i, 0, 0, 0);
                break;
        }
    }
    if(hitFlag)
    {
        UART_Write(0x02);
    }
    else
    {
        UART_Write(0x01);
    }
}

void Step::Update(void)
{
    if(x >= 23)
    {
        unsigned char button_index;
        switch(y)
        {
            case LEFT_Y:
                button_index = 0;
                break;
            case DOWN_B:
                button_index = 1;
                break;
            case UP_X:
                button_index = 2;
                break;
            case RIGHT_A:
                button_index = 3;
                break;
        }
        if(get_ButtonState(button_index) == 1)
        {
            hitFlag = true;
        }
    }
    
    elapsed_time += 5;//get_ListPeriod();
    
    if(elapsed_time >= UPDATE_TIME)
    {
        elapsed_time = 0;
        
        for(unsigned char i = y; i < y+3; i++)
        {
            switch(x)
            {
                case 0:
                    matrix_DrawPixel(x, i, r, g, b);
                    break;
                case 25:
                    matrix_DrawPixel(24, i, 20, 20, 20);
                    matrix_DrawPixel(x, i, r, g, b);
                    break;
                case 27:
                    matrix_DrawPixel(26, i, 20, 20, 20);
                    break;
                default:
                    matrix_DrawPixel((x - 1), i, 0, 0, 0);
                    matrix_DrawPixel(x, i, r, g, b);
                    break;
            }
        }
        x++;
    }
}

unsigned char Step::getX(void) { return x; }

/*
void StepHead::Update(void)
{
    elapsed_time += 5;
    
    if(elapsed_time >= UPDATE_TIME)
    {
        elapsed_time = 0;
        
        for(unsigned char i = y; i < y+3; i++)
        {
            switch(x)
            {
                case 0:
                    matrix_DrawPixel(x, i, r, g, b);
                    break;
                default:
                    matrix_DrawPixel((x - 1), i, 0, 10, 80);
                    matrix_DrawPixel(x, i, r, g, b);
                    break;
            }
        }
        
        if(next != NULL)
        {
            next->Update();
        }      
        x++;
    } 
}

void StepBody::Update(void)
{
    elapsed_time += 5;
    
    if(elapsed_time >= UPDATE_TIME)
    {
        elapsed_time = 0;
        
        for(unsigned char i = y; i < y+3; i++)
        {
            matrix_DrawPixel(x, i, r, g, b);
        }
        
        if(next != NULL)
        {
            next->Update();
        }
        x++;
    } 
}

void StepTail::Update(void)
{
    elapsed_time += 5;
    
    if(elapsed_time >= UPDATE_TIME)
    {
        elapsed_time = 0;
        
        for(unsigned char i = y; i < y+3; i++)
        {
            matrix_DrawPixel(x, i, r, g, b);
        }
        x++;
    } 
}
*/

void make_Steps(unsigned char data, unsigned char beat, LinkedList<Step*> &list)
{
    
    //Left, Down, Up, Right
    unsigned char datas[4] = { ((data>>6) & 0x03), ((data>>4) & 0x03), ((data>>2) & 0x03), (data & 0x03) };
    unsigned char ys[4] = {LEFT_Y, DOWN_B, UP_X, RIGHT_A};
    unsigned char colors[4][3] = {
            {100,0,0},
            {100,70,0},
            {0,0,100},
            {100,70,0},
        };
    
    for(unsigned char i = 0; i < 4; i++)
    {
        Step *step;
        switch(datas[i])
        {
            case 0x00:
            /*
                if(last_step[i] != NULL)
                {
                    step = new StepBody(ys[i]);
                    last_step[i]->next = step;
                    last_step[i] = last_step[i]->next;
                }
               */
                break;
                
            case 0x01:
                step = new Step(ys[i],colors[beat]);
                list.add(step);
                break;
                
            case 0x02:
            
                step = new Step(ys[i],colors[beat]);
                list.add(step);
                
                break;
                
            case 0x03:
            /*
                if(last_step[i] != NULL)
                {
                    step = new StepTail(ys[i]);
                    last_step[i]->next = step;
                    last_step[i] = NULL;
                }
                */
                break;
        }
    }
}