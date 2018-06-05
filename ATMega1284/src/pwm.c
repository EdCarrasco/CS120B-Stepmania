#include "pwm.h"

#define CSn2 2
#define CSn1 1
#define CSn0 0
#define COMnA0 6

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t *TCCRnA[3] = {&TCCR0A, &TCCR2A, &TCCR3A};
volatile uint8_t *TCCRnB[3] = {&TCCR0B, &TCCR2B, &TCCR3B};
volatile uint8_t *OCRn[3] = {&OCR0A, &OCR2A, &OCR3AL};
volatile uint8_t *TCNTn[3] = {&TCNT0, &TCNT2, &TCNT3L};

/*
PB7 - OCR3B
PB6 - OCR3A

PB4 - OCR0B
PB3 - OCR0A

PD7 - OCR2A
PD6 - OCR2B

PD5 - OCR1A
PD4 - OCR1B
*/

void PWM_off(unsigned char channel) {
    *TCCRnA[channel] = 0x00;
    *TCCRnB[channel] = 0x00;
}

void PWM_on(unsigned char channel, float prescaler) {
    // COMnA0: Toggle port channel to compare match between counter and OCRn
    // WGMn2: When counter (TCNTn) matches OCRn, reset counter
    // CSn[2:0]: Set a prescaler
    
    switch(channel)
    {
        case 0:
            *TCCRnA[channel] = (1 << COMnA0) | (1 << WGM01);
            if(prescaler == 64) { *TCCRnB[channel] = (1 << CSn1) | (1 << CSn0); }
            else if(prescaler == 256) { *TCCRnB[channel] = (1 << CSn2); }
            else if(prescaler == 1024) { *TCCRnB[channel] = (1 << CSn2) | (1 << CSn0); }
            break;
        case 1:
            *TCCRnA[channel] = (1 << COMnA0) | (1 << WGM21);
            if(prescaler == 64) { *TCCRnB[channel] = (1 << CSn2); }
            else if(prescaler == 256) { *TCCRnB[channel] = (1 << CSn2) | (1 << CSn1); }
            else if(prescaler == 1024) { *TCCRnB[channel] = (1 << CSn2) | (1 << CSn1) | (1 << CSn0); }
            break;
        case 2:
            *TCCRnA[channel] = (1 << COMnA0);
            *TCCRnB[channel] = (1 << WGM32);
            if(prescaler == 64) { *TCCRnB[channel] |= (1 << CSn1) | (1 << CSn0); }
            else if(prescaler == 256) { *TCCRnB[channel] |= (1 << CSn2); }
            else if(prescaler == 1024) { *TCCRnB[channel] |= (1 << CSn2) | (1 << CSn0); }
            break;
        default:
            break;
    }
}

// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(unsigned char channel, float frequency)
{
    //static float current_frequency[3]; // Keeps track of the currently set frequency
    
    //if(frequency != current_frequency[channel]) // Only update registers when frequency changes
    //{
        float prescaler;
        if(frequency < 61.0352) { prescaler = 1024; }
        else if(frequency < 244.1407) {prescaler = 256; }
        else {prescaler = 64; }
        
        if (!frequency) { PWM_off(channel); } //stops timer/counter
        else { PWM_on(channel, prescaler); } // resumes/continues timer/counter
        
        // prevents OCRn from overflowing 8-bit counter, using prescaler 1024
        // 15.2588 is smallest frequency that will not result in overflow
        if (frequency < 15.2588) { *OCRn[channel] = 0xFF; }
        
        // prevents OCRn from underflowing, using prescaler 64
        // 31250 is largest frequency that will not result in underflow
        else if (frequency > 31250) { *OCRn[channel] = 0x00; }
        
        // set OCRn based on desired frequency
        // ((8 MHz / prescaler) * (1/2) * (1/frequency)) -1
        else { *OCRn[channel] = (unsigned char)(4000000 / (prescaler * frequency)) - 1; }

        *TCNTn[channel] = 0; // resets counter
        //current_frequency[channel] = frequency; // Updates the current frequency
    //}
}