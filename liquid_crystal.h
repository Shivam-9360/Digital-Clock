#ifndef _LIQUID_CRYSTAL_H_
#define _LIQUID_CRYSTAL_H_

#include "timer.h"
#include "pin_mapping.h"
#include "print.h"

#define LCD_ROWS                2
#define LCD_COLS                16
#define LCD_REFRESH_RATE_MS     750

class LCDDisplay : public Print {
public:
  void setup(void);
  void loop(void);
  
  void setCursor(unsigned char xIndex, unsigned char yIndex);
  
protected:
  // write interface
  unsigned short int write(char character);
  unsigned short int write(const char* str);
  unsigned short int write(const char* str, unsigned char size);
  
private:
  enum LCDState {
    POWER_ON_WAIT,
    LCD_INIT,
    LCD_LOOP
  };
  
  unsigned short int lcdMillis;
  LCDState state;
  
  // frame buffer related variable
  char frameBuffer [LCD_ROWS][LCD_COLS];
  unsigned char cursorX;
  unsigned char cursorY;
  
  void updateDisplay(void);
  
  void transmitCommand(char command);
  void transmitData(char data);
  void toggleEN(void);
  
  unsigned char generateGoToXYCommand(unsigned char inputXIndex, unsigned char yIndex);  
  
  void blockingDelayMS(unsigned int delayVal);
};

#endif