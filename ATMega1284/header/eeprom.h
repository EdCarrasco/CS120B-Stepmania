#ifndef __eeprom_h__
#define __eeprom_h__

void EEPROM_Write(unsigned int address, unsigned char data);
unsigned char EEPROM_Read(unsigned int address);

#endif