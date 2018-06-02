#ifndef __notes_h__
#define __notes_h__
#include <math.h>

#define C8 88

#define B7 87
#define Bb7 As7
#define As7 86
#define A7 85
#define Ab7 Gs7
#define Gs7 84
#define G7 83
#define Gb7 Fs7
#define Fs7 82
#define F7 81
#define E7 80
#define Eb7 Ds7
#define Ds7 79
#define D7 78
#define Db7 Cs7
#define Cs7 77
#define C7 76

#define B6 75
#define Bb6 As6
#define As6 74
#define A6 73
#define Ab6 Gs6
#define Gs6 72
#define G6 71
#define Gb6 Fs6
#define Fs6 70
#define F6 69
#define E6 68
#define Eb6 Ds6
#define Ds6 67
#define D6 66
#define Db6 Cs6
#define Cs6 65
#define C6 64

#define B5 63
#define Bb5 As5
#define As5 62
#define A5 61
#define Ab5 Gs5
#define Gs5 60
#define G5 59
#define Gb5 Fs5
#define Fs5 58
#define F5 57
#define E5 56
#define Eb5 Ds5
#define Ds5 55
#define D5 54
#define Db5 Cs5
#define Cs5 53
#define C5 52

#define B4 51
#define Bb4 As4
#define As4 50
#define A4 49
#define Ab4 Gs4
#define Gs4 48
#define G4 47
#define Gb4 Fs4
#define Fs4 46
#define F4 45
#define E4 44
#define Eb4 Ds4
#define Ds4 43
#define D4 42
#define Db4 Cs4
#define Cs4 41
#define C4 40

#define B3 39
#define Bb3 As3
#define As3 38
#define A3 37
#define Ab3 Gs3
#define Gs3 36
#define G3 35
#define Gb3 Fs3
#define Fs3 34
#define F3 33
#define E3 32
#define Eb3 Ds3
#define Ds3 31
#define D3 30
#define Db3 Cs3
#define Cs3 29
#define C3 28

#define B2 27
#define Bb2 As2
#define As2 26
#define A2 25
#define Ab2 Gs2
#define Gs2 24
#define G2 23
#define Gb2 Fs2
#define Fs2 22
#define F2 21
#define E2 20
#define Eb2 Ds2
#define Ds2 19
#define D2 18
#define Db2 Cs2
#define Cs2 17
#define C2 16

#define B1 15
#define Bb1 As1
#define As1 14
#define A1 13
#define Ab1 Gs1
#define Gs1 12
#define G1 11
#define Gb1 Fs1
#define Fs1 10
#define F1 9
#define E1 8
#define Eb1 Ds1
#define Ds1 7
#define D1 6
#define Db1 Cs1
#define Cs1 5
#define C1 4

#define B0 3
#define Bb0 As0
#define As0 2
#define A0 1

inline float get_Frequency(unsigned char n)
{
    return n > 0 ? (float)pow(2,(((float)n-49)/12)) * 440.0 : 0;
}

#endif