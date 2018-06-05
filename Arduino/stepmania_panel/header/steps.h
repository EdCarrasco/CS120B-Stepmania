#ifndef __steps_h__
#define __steps_h__

#include "../header/LinkedList.h"

class Step
{
protected:
    unsigned char x;
    unsigned char y;

    unsigned char r;
    unsigned char g;
    unsigned char b;
    
    unsigned char elapsed_time;
    
public:
    Step(unsigned char Y, unsigned char COLOR[3]);
    Step(unsigned char Y, unsigned char R, unsigned char G, unsigned char B);
    ~Step();
    void Update(void);
    unsigned char getX(void);
};

class StepHold : public Step
{
public:
    StepHold* next;
    StepHold(unsigned char Y, unsigned char COLOR[3]) : Step(Y, COLOR[3]) {}
    StepHold(unsigned char Y, unsigned char R, unsigned char G, unsigned char B) : Step(Y,R,G,B) {}
};

class StepHead : public StepHold
{
public:
    StepHead(unsigned char Y, unsigned char COLOR[3]) : StepHold(Y, COLOR[3]) {}
    StepHead(unsigned char Y, unsigned char R, unsigned char G, unsigned char B) : StepHold(Y,R,G,B) {}
    void Update(void);
};

class StepBody : public StepHold
{
public:
    StepBody(unsigned char Y) : StepHold(Y,0,10,80) {}
    void Update(void);
};

class StepTail : public StepHold
{
public:
    StepTail(unsigned char Y) : StepHold(Y,0,10,80) {}
    void Update(void);
};

void make_Steps(unsigned char data, unsigned char beat, LinkedList<Step*> &list);

#endif