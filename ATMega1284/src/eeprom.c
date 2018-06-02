#include <avr/io.h>
#include "eeprom.h"

void EEPROM_Write(unsigned int address, unsigned char data)
{
	//Wait for previous write to finish
	while(EECR & (1 << EEPE));
	
	// Set up address and data registers
	EEAR = address;
	EEDR = data;
	
	// Enable writing
	EECR |= (1 << EEMPE);
	
	// Begin Write
	EECR |= (1 << EEPE);
}

unsigned char EEPROM_Read(unsigned int address)
{
	//Wait for previous write to finish
	while(EECR & (1 << EEPE));
	
	// Set up address register
	EEAR = address;
	
	// Begin Read
	EECR |= (1 << EERE);
	
	//Return data register
	return EEDR;
}