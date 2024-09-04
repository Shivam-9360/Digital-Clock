#include "timer.h"

// global variables
volatile unsigned short int tenMillis = 0U;
const volatile unsigned short int& millis = tenMillis;

// function prototyping
__interrupt void timer0_isr(void);

void timerSetup(void) {
  // timer mode: 16-bit mode
  TMOD = 0x01U;
  
  // timer reload value
  TL0 = static_cast<unsigned char>(TIMER_RELOAD_VALUE);
  TH0 = static_cast<unsigned char>(TIMER_RELOAD_VALUE >> 8);
  
  // enable interrupt
  IE_bit.ET0 = 1;
  IE_bit.EA = 1;
  
  // start timer
  TCON_bit.TR0 = 1;
}

#pragma vector = timer0
__interrupt void timer0_isr(void)
{
  // timer reload value
  TL0 = static_cast<unsigned char>(TIMER_RELOAD_VALUE);
  TH0 = static_cast<unsigned char>(TIMER_RELOAD_VALUE >> 8);
  
  tenMillis++;
}