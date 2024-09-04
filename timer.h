#ifndef _TIMER_H_
#define _TIMER_H_

#include <ioAT89S52.h>

// settings
#define FREQ_OSC                11059200
#define BASE_DELAY_MS           10

#define TIMER_RELOAD_VALUE      (65536 - (FREQ_OSC * BASE_DELAY_MS / 12000))
#define MILLS_DELAY(value)      (value / BASE_DELAY_MS)

// extern variables
extern const volatile unsigned short int& millis;

// function prototyping
void timerSetup(void);

#endif