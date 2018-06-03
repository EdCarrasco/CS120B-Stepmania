#ifndef __steps_h__
#define __steps_h__

class Step
{
private:
    unsigned char x;
    unsigned char y;

    unsigned char r;
    unsigned char g;
    unsigned char b;
    
public:
    Step(unsigned char X,unsigned char Y,unsigned char R,unsigned char G,unsigned char B) :
        x(X), y(Y), r(R), g(G), b(B) {}
    ~Step() {}
};

#endif