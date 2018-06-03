#include "../header/globals.h"

unsigned char controller_data;
void set_ControllerData(unsigned char data) { controller_data = data; }
unsigned char get_ControllerData(void) { return controller_data; }