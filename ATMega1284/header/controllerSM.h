#ifndef __controllerSM_h__
#define __controllerSM_h__

int Tick_Controller(int state);
int (*controller_GetTick())(int);

#endif