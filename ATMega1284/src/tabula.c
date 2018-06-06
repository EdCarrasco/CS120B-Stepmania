#include "tabula.h"
#include "notes.h"

// (60000 / (note prescaler * standard tempo ))
//  mathmetically, this should be 60000/(4*150) = 100, but it plays too slowly
#define TEMPO 95

static const unsigned char tabula_track1[][2] = {
    {0, 2}, {A5, 2}, {0, 2}, {A5, 2}, {0, 2}, {Gs5, 2}, {0, 2}, {Gs5, 2},
    {0, 2}, {A5, 2}, {0, 2}, {A5, 2}, {Gs5, 2}, {A5, 2}, {B5, 2}, {Cs6, 2},
    {0, 2}, {A5, 2}, {0, 2}, {A5, 2}, {0, 2}, {Gs5, 2}, {0, 2}, {Gs5, 2},
    {0, 2}, {A5, 2}, {0, 2}, {A5, 2}, {Gs5, 2}, {A5, 2}, {B5, 2}, {Cs5, 1},  {E5, 1}, //33
    
    {Fs5, 12}, {0, 2}, {Cs5, 1}, {E5, 1},
    {Fs5, 4}, {A5, 4}, {Gs5, 2}, {E5, 4}, {Cs5, 1}, {E5, 1},
    {Fs5, 16},
    {0, 12}, {Cs4, 2}, {E4, 2}, // 14
    
    {Fs4, 6}, {A4, 2}, {Gs4, 2}, {A4, 1}, {Gs4, 1}, {Fs4, 2}, {E4, 2},
    {E4, 1}, {Fs4, 1}, {Cs4, 4}, {B3, 2}, {Cs4, 4}, {B3, 2}, {A3, 2},
    {B3, 6}, {A3, 2}, {Gs3, 2}, {B3, 2}, {E4, 2}, {Fs4, 2},
    {Cs4, 12}, {Cs4, 2}, {E4, 2}, // 23
    
    {Fs4, 6}, {A4, 2}, {Gs4, 2}, {A4, 1}, {Gs4, 1}, {Fs4, 2}, {E4, 2},
    {E4, 1}, {Fs4, 1}, {Cs4, 4}, {B3, 2}, {Cs4, 4}, {B3, 2}, {A3, 2},
    {B3, 6}, {A3, 2}, {Gs3, 4}, {E3, 4},
    {Fs3, 2}, {Cs3, 2}, {Gs3, 2}, {Cs3, 2}, {A3, 4}, {A3, 2}, {B3, 2}, // 25
    
    {Cs4, 12}, {E4, 2}, {Fs4, 2},
    {Cs4, 12}, {B3, 2}, {A3, 2},
    {B3, 6}, {A3, 2}, {Gs3, 2}, {B3, 2}, {E4, 2}, {Fs4, 2},
    {Cs4, 12}, {Fs4, 2}, {E4, 2}, // 15
    
    {Fs4, 6}, {E4, 2}, {Fs4, 2}, {B3, 2}, {Cs4, 2}, {E4, 2},
    {A3, 2}, {B3, 2}, {Cs4, 2}, {Gs4, 2}, {A4, 4}, {A4, 2}, {B4, 2},
    {A4, 2}, {Gs4, 2}, {Fs4, 2}, {A4, 2}, {Gs4, 2}, {Fs4, 2}, {E4, 2}, {Gs4, 2},
    {Fs4, 2}, {Gs4, 2}, {A4, 2}, {B4, 2}, {Cs5, 4}, {Cs5, 2}, {E5, 2}, // 28
    
    {Cs5, 8}, {E5, 4}, {Cs5, 2}, {E5, 2},
    {Cs5, 4}, {Gs5, 4}, {A5, 4}, {Gs5, 4},
    {Fs5, 2}, {E5, 2}, {Cs5, 2}, {Fs5, 2}, {E5, 2}, {B4, 2}, {Gs4, 2}, {E5, 2},
    {Cs5, 4}, {B4, 4}, {Cs5, 4}, {A4, 2}, {B4, 2}, // 21
    
    {Cs5, 8}, {E5, 4}, {Cs5, 2}, {E5, 2},
    {Cs5, 4}, {Gs5, 4}, {A5, 4}, {B5, 4},
    {A5, 2}, {Gs5, 2}, {Fs5, 2}, {A5, 2}, {Gs5, 2}, {E5, 2}, {B4, 2}, {E5, 2},
    {Cs5, 2}, {E5, 2}, {B4, 2}, {Cs5, 2}, {A4, 2}, {A4, 2}, {Gs4, 4}, // 23
    
    {Cs5, 8}, {E5, 4}, {Cs5, 2}, {E5, 2},
    {Cs5, 4}, {Gs5, 4}, {A5, 4}, {Gs5, 4},
    {Fs5, 2}, {E5, 2}, {Cs5, 2}, {Fs5, 2}, {E5, 2}, {B4, 2}, {Gs4, 2}, {E5, 2},
    {Cs5, 4}, {B4, 4}, {Cs5, 4}, {A4, 2}, {B4, 2}, // 21
    
    {Cs5, 8}, {E5, 4}, {Cs5, 2}, {E5, 2},
    {Cs5, 4}, {Gs5, 4}, {A5, 4}, {B5, 4},
    {A5, 2}, {Gs5, 2}, {Fs5, 2}, {A5, 2}, {Gs5, 2}, {E5, 2}, {B4, 2}, {E5, 2},
    {Fs5,12} // 17
};

static const unsigned char tabula_track2[][2] = {
    {0, 2}, {Cs4, 2}, {0, 2}, {Cs4, 2}, {0, 2}, {B3, 2}, {0, 2}, {B3, 2},
    {0, 2}, {A3, 2}, {0, 2}, {A3, 2}, {0, 2}, {B3, 2}, {0, 2}, {B3, 2},
    {0, 2}, {Cs4, 2}, {0, 2}, {Cs4, 2}, {0, 2}, {B3, 2}, {0, 2}, {B3, 2},
    {0, 2}, {A3, 2}, {0, 2}, {A3, 2}, {0, 2}, {B3, 2}, {0, 2}, {B3, 2}, // 32
    
    {0, 2}, {A5, 2}, {0, 2}, {A5, 2}, {0, 2}, {Gs5, 2}, {0, 2}, {Gs5, 2},
    {0, 2}, {A5, 2}, {0, 2}, {A5, 2}, {Gs5, 2}, {A5, 2}, {B5, 2}, {Cs6, 2},
    {0, 2}, {A5, 2}, {0, 2}, {A5, 2}, {0, 2}, {Gs5, 2}, {0, 2}, {Gs5, 2},
    {0, 2}, {A5, 2}, {0, 2}, {A5, 2}, {Gs5, 2}, {A5, 2}, {B5, 2}, {Cs6, 2}, //32
    
    {0, 16},
    {0, 16},
    {0, 16},
    {Gs3, 2}, {Cs4, 2}, {A3, 2}, {B3, 2}, {Cs4, 2}, {Cs4, 1}, {B3, 1}, {A3, 2}, {Gs3, 2}, // 12
    
    {0, 16},
    {0, 16},
    {0, 16},
    {0, 16}, //4
    
    {0, 4}, {Cs5, 2}, {E5, 2}, {Fs5, 8},
    {0, 4}, {Cs5, 2}, {E5, 2}, {Fs5, 8},
    {0, 4}, {Cs5, 2}, {E5, 2}, {Fs5, 2}, {Cs5, 2}, {Gs5, 2}, {A5, 2},
    {A5, 8}, {Gs5, 8}, // 17
    
    {Fs5, 6}, {E5, 2}, {Fs5, 2}, {B4, 2}, {Cs5, 2}, {E5, 2},
    {A4, 2}, {B4, 2}, {Cs5, 2}, {Gs5, 2}, {A5, 4}, {A5, 2}, {B5, 2},
    {A5, 2}, {Gs5, 2}, {Fs5, 2}, {A5, 2}, {Gs5, 2}, {Fs5, 2}, {E5, 2}, {Gs5, 2},
    {Fs5, 2}, {Gs5, 2}, {A5, 2}, {B5, 2}, {Cs6, 4}, {0, 4}, // 27
    
    {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3,2}, {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3, 2},
    {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3,2}, {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3, 2},
    {B2, 2}, {A3, 2}, {Gs3, 2}, {A3,2}, {0, 2}, {B3, 2}, {E3, 2}, {Gs3, 2},
    {Fs3, 2}, {A3, 2}, {Gs3, 2}, {E3, 2}, {Cs3, 2}, {A2, 2}, {Cs2, 2}, {E2, 2}, //32
    
    {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3,2}, {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3, 2},
    {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3,2}, {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3, 2},
    {B2, 2}, {A3, 2}, {Gs3, 2}, {A3,2}, {E3, 2}, {B3, 2}, {A3, 2}, {B3, 2},
    {D3, 2}, {Fs3, 2}, {E3, 2}, {Gs3, 2}, {A2, 2}, {Fs3, 2}, {E3, 2}, {B2, 2}, //32
    
    {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3,2}, {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3, 2},
    {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3,2}, {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3, 2},
    {B2, 2}, {A3, 2}, {Gs3, 2}, {A3,2}, {0, 2}, {B3, 2}, {E3, 2}, {Gs3, 2},
    {Fs3, 2}, {A3, 2}, {Gs3, 2}, {E3, 2}, {Cs3, 2}, {A2, 2}, {Cs2, 2}, {E2, 2}, //32
    
    {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3,2}, {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3, 2},
    {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3,2}, {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3, 2},
    {B2, 2}, {A3, 2}, {Gs3, 2}, {A3,2}, {E3, 2}, {B3, 2}, {A3, 2}, {B3, 2},
    {Cs3, 2}, {Fs3, 2}, {E3, 2}, {Fs3, 2}, {Fs2, 8} // 29
};

static const unsigned char tabula_track3[][2] = {
    {Fs2, 2}, {Fs3, 2}, {Cs3, 2}, {Fs3, 2}, {E2, 2}, {E3, 2}, {B2, 2}, {E3, 2},
    {D2, 2}, {D3, 2}, {A2, 2}, {D3, 2}, {E2, 2}, {E3, 2}, {B2, 2}, {Cs3, 2},
    {Fs2, 2}, {Fs3, 2}, {Cs3, 2}, {Fs3, 2}, {E2, 2}, {E3, 2}, {B2, 2}, {E3, 2},
    {D2, 2}, {D3, 2}, {A2, 2}, {D3, 2}, {E2, 2}, {E3, 2}, {B2, 2}, {Cs3, 2}, // 32
    
    {Fs2, 2}, {Fs3, 2}, {Cs3, 2}, {Fs3, 2}, {E2, 2}, {E3, 2}, {B2, 2}, {E3, 2},
    {D2, 2}, {D3, 2}, {A2, 2}, {D3, 2}, {E2, 2}, {E3, 2}, {B2, 2}, {Cs3, 2},
    {Fs2, 2}, {Fs3, 2}, {Cs3, 2}, {Fs3, 2}, {E2, 2}, {E3, 2}, {B2, 2}, {E3, 2},
    {D2, 2}, {D3, 2}, {A2, 2}, {D3, 2}, {E2, 2}, {E3, 2}, {B2, 2}, {E3, 2}, // 32
    
    {Fs2, 2}, {Cs3, 2}, {Fs2, 2}, {Cs3, 2}, {Fs2, 2}, {Cs3, 2}, {Fs2, 2}, {Cs3, 2},
    {D2, 2}, {A2, 2}, {D2, 2}, {A2, 2}, {D2, 2}, {A2, 2}, {D2, 2}, {A2, 2},
    {E2, 2}, {B2, 2}, {E2, 2}, {B2, 2}, {E2, 2}, {B2, 2}, {E2, 2}, {B2, 2},
    {Fs2, 2}, {Cs2, 2}, {Fs2, 2}, {Cs2, 2}, {F2, 2}, {Cs2, 2}, {F2, 2}, {Cs2, 2}, // 32
    
    {Fs2, 2}, {Cs3, 2}, {Fs2, 2}, {Cs3, 2}, {Fs2, 2}, {Cs3, 2}, {Fs2, 2}, {Cs3, 2},
    {D2, 2}, {A2, 2}, {D2, 2}, {A2, 2}, {D2, 2}, {A2, 2}, {D2, 2}, {A2, 2},
    {E2, 2}, {B2, 2}, {E2, 2}, {B2, 2}, {E2, 2}, {B2, 2}, {E2, 2}, {B2, 2},
    {Fs2, 2}, {Cs2, 2}, {Fs2, 2}, {Cs2, 2}, {F2, 2}, {Cs2, 2}, {F2, 2}, {Cs2, 2}, // 32
    
    {Fs3, 6}, {Fs2, 2}, {Fs2, 8},
    {Fs3, 6}, {Fs2, 2}, {Fs2, 8},
    {E3, 6}, {E3, 2}, {E3, 8},
    {D3, 8}, {E3, 8}, // 11
    
    {Fs2, 2}, {Cs3, 2}, {Fs2, 2}, {Cs3, 2}, {Fs2, 2}, {Cs3, 2}, {Fs2, 2}, {Cs3, 2},
    {D2, 2}, {A2, 2}, {D2, 2}, {A2, 2}, {D2, 2}, {A2, 2}, {D2, 2}, {A2, 2},
    {E2, 2}, {B2, 2}, {E2, 2}, {B2, 2}, {E2, 2}, {B2, 2}, {E2, 2}, {B2, 2},
    {Fs2, 2}, {Gs2, 2}, {A2, 2}, {B2, 2}, {Cs3, 2}, // 29
    
    {Fs2, 16},
    {A2, 16},
    {A2, 8}, {Fs2, 4}, {Gs2, 4},
    {A2, 8}, {Cs3, 8}, // 7
    
    {Fs2, 16},
    {A2, 16},
    {A2, 8}, {B2, 8},
    {Fs2, 4}, {Gs2, 4}, {A2, 2}, {Fs2, 2}, {E2, 4}, // 9
    
    {Fs2, 16},
    {A2, 16},
    {A2, 8}, {Fs2, 4}, {Gs2, 4},
    {A2, 8}, {Cs3, 8}, // 7
    
    {Fs2, 16},
    {A2, 16},
    {A2, 8}, {B2, 8},
    {Fs2, 12} // 9
};

//TODO Fix Map

// Left, Down, Up, Right -- Y, B, X, A
// 00 off, 01 hit, 10 hold, 11 release
static const unsigned char tabula_map[] =
{
	
    // Measure 1
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000001,
    0b00000000,
    
    // Measure 2
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000100,
    0b00000000,
    
    // Measure 3
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000001,
    0b00000000,
    
    // Measure 4
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00010000,
    0b01000000,
	
	
    // Measure 5
    0b00001000, // hold
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00001100, // release
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00010000,
    0b01000000,
    
    // Measure 6
    0b00000010, // hold
    0b00000000,
    0b00000011, // release
    0b00000000,
    0b00001000, // hold
    0b00000000,
    0b00001100, // release
    0b00000000,
    0b00000001,
    0b00000000,
    0b10000000, // hold
    0b00000000, 
    0b11000000,// release
    0b00000000,
    0b00010000,
    0b01000000,
    
    // Measure 7
    0b00001000, // hold
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00001100, // release
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    
    // Measure 8
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    
    
    // Measure 9
    0b00000010,
    0b00000000,
    0b00000011,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000100,
    0b00000001,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    
    // Measure 10
    0b00010000,
    0b01000000,
    0b00000010,
    0b00000000,
    0b00000011,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    
    // Measure 11
    0b10000000,
    0b00000000,
    0b11000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000100,
    0b00000000,
    
    // Measure 12
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000100,
    0b00000001,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    
    // Measure 13
    0b00000010,
    0b00000000,
    0b00000011,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000100,
    0b00000001,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    
    // Measure 14
    0b00010000,
    0b01000000,
    0b00000010,
    0b00000000,
    0b00000011,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    
    // Measure 15
    0b10000000,
    0b00000000,
    0b11000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000000,
    0b00000000,
    
    // Measure 16
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,

    // Measure 17
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    
    // Measure 18
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    
    // Measure 19
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000100,
    0b00000000,
    
    // Measure 20
    0b00000010,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01000011, //Edited
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000001,
    0b00000000,
    
    // Measure 21
    0b00001000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00001100,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000001,
    0b00000000,
    
    // Measure 22
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000001,
    0b00000000,
    
    // Measure 23
    0b00000100,
    0b00000000,
    0b00000001,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000001,
    0b00000000,
    
    // Measure 24
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000100,
    0b00000000,
    
    // Measure 25
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000100,
    0b00000000,
    
    // Measure 26
    0b00010000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    
    // Measure 27
    0b00000100,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000001,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000001,
    0b00000000,
    
    // Measure 28
    0b01000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    
    // Measure 29
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000100,
    0b00000000,
    
    // Measure 30
    0b00010000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000000,
    0b00000000,
    
    // Measure 31
    0b00000001,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000001,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000100,
    0b00000000,
    
    // Measure 32
    0b01000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000000,
    0b00000000,
    
    // Measure 33
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000100,
    0b00000000,
    
    // Measure 34
    0b00010000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    
    // Measure 35
    0b00000100,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000001,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000001,
    0b00000000,
    
    // Measure 36
    0b01000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b01000000,
    0b00000000,
    
    // Measure 37
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000100,
    0b00000000,
    
    // Measure 38
    0b00010000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000001,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000000,
    0b00000000,
    
    // Measure 39
    0b00000001,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000001,
    0b00000000,
    0b01000000,
    0b00000000,
    0b00010000,
    0b00000000,
    0b00000100,
    0b00000000,
    
    // Measure 40
    0b10000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b11000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};

float get_Tabula_Tone(unsigned char track, unsigned char index)
{ 
    switch(track)
    {
        case 0:
            return get_Frequency(tabula_track1[index][0]);
            break;
        case 1:
            return get_Frequency(tabula_track2[index][0]);
            break;
        case 2:
            return get_Frequency(tabula_track3[index][0]);
            break;
        default:
            return 0;
            break;
    }
}

unsigned long get_Tabula_Duration(unsigned char track, unsigned char index)
{
    switch(track)
    {
        case 0:
            return (unsigned long)tabula_track1[index][1] * TEMPO;
            break;
        case 1:
            return (unsigned long)tabula_track2[index][1] * TEMPO;
            break;
        case 2:
            return (unsigned long)tabula_track3[index][1] * TEMPO;
            break;
        default:
            return 0;
            break;
    }
}

unsigned char get_Tabula_Size(unsigned char track)
{ 
    switch(track)
    {
        case 0:
            return sizeof tabula_track1 / sizeof *tabula_track1;
            break;
        case 1:
            return sizeof tabula_track2 / sizeof *tabula_track2;
            break;
        case 2:
            return sizeof tabula_track3 / sizeof *tabula_track3;
            break;
        default:
            return 0;
            break;
    }
}

const unsigned char* get_Tabula_Map() { return tabula_map; }

//unsigned char get_Tabula_Map(unsigned char index) { return tabula_map[index]; }

unsigned short get_Tabula_Map_Size() { return sizeof tabula_map / sizeof *tabula_map; }
	
unsigned short get_Tabula_Tempo() { return TEMPO; }