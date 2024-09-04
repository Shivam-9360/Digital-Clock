#include "liquid_crystal.h"

void LCDDisplay::setup(void) {
  // clear state
  state = POWER_ON_WAIT;
  lcdMillis = millis;
  
  // clear frame buffer
  for(unsigned char rowIndex = 0; rowIndex < LCD_ROWS; rowIndex++) {
    for(unsigned char colIndex = 0; colIndex < LCD_COLS; colIndex++) {
      frameBuffer[rowIndex][colIndex] = ' ';
    }
  }
  
  cursorX = 0;
  cursorY = 0;
}

void LCDDisplay::loop(void) {
  switch(state) {
    case POWER_ON_WAIT: {
      if((millis - lcdMillis) > MILLS_DELAY(100)) {
        state = LCD_INIT;
      }
    } break;
    
    case LCD_INIT: {
       transmitCommand(0x38);   // initilize the lcd in 8bit mode
       transmitCommand(0x0E);   // display on cursor off
       transmitCommand(0x01);   // clear the lcd
       transmitCommand(0x80);   // move the cursor to first line first position
       transmitCommand(0x01);   // clear the lcd
       
       lcdMillis = millis;
       state = LCD_LOOP;
    } break;
    
    case LCD_LOOP: {
      if((millis - lcdMillis) > MILLS_DELAY(LCD_REFRESH_RATE_MS)) {
        lcdMillis = millis;
        updateDisplay();
      }
    } break;
    
    default: {
      // do nothing
    } break;
  }
}

void LCDDisplay::setCursor(unsigned char xIndex, unsigned char yIndex) {
  if (xIndex >= LCD_COLS) {
    cursorX = LCD_COLS - 1;
  } else {
    cursorX = xIndex;
  }
  
  if (yIndex >= LCD_ROWS) {
    cursorY = LCD_ROWS - 1;
  } else {
    cursorY = yIndex;
  }
}

void LCDDisplay::updateDisplay(void) {
  for(unsigned char rowIndex = 0; rowIndex < LCD_ROWS; rowIndex++) {
    transmitCommand(generateGoToXYCommand(0, rowIndex));
    for(unsigned char colIndex = 0; colIndex < LCD_COLS; colIndex++) {
      transmitData(frameBuffer[rowIndex][colIndex]);
    }
  }
}

void LCDDisplay::transmitCommand(char command) {
   LCD_RS = 0;
   LCD_DATA = command;
   toggleEN();
}

void LCDDisplay::transmitData(char data) {
   LCD_RS = 1;
   LCD_DATA = data;
   toggleEN();
}

void LCDDisplay::toggleEN(void) {
   LCD_EN = 1;
   blockingDelayMS(2);
   LCD_EN = 0;
   blockingDelayMS(2);
}

void LCDDisplay::blockingDelayMS(unsigned int delayVal) {
  unsigned int outerLoopVar, innerLoopVar;
  
  for(outerLoopVar = 0; outerLoopVar < delayVal; outerLoopVar++) {
    for(innerLoopVar = 0; innerLoopVar < 127; innerLoopVar++) {
      // do nothing
    }
  }
}

unsigned char LCDDisplay::generateGoToXYCommand(unsigned char inputXIndex, unsigned char yIndex) {
    unsigned char xIndex = inputXIndex;
    unsigned char returnVar;
    
    if (xIndex >= LCD_COLS) {
        xIndex = LCD_COLS - 1;
    }

    switch (yIndex) {
        case 0: {
            returnVar = 0x00;
        } break;

        case 1: {
            returnVar = 0x40;
        } break;

        default: {
            returnVar = 0x00;
        } break;
    }

    returnVar = returnVar + xIndex;
    returnVar = 0x80 | returnVar;
    
    return returnVar;
}  

unsigned short int LCDDisplay::write(char character) {
  frameBuffer[cursorY][cursorX] = character;
  
  cursorX++;
  if(cursorX >= LCD_COLS) {
    cursorX = 0;
    cursorY++;
    if(cursorY >= LCD_ROWS) {
      cursorY = 0;
    }
  }
  
  return 1;
}

unsigned short int LCDDisplay::write(const char* str) {
  unsigned char bytesPrinted = 0;
  
  for(unsigned char loopVar = 0; loopVar < LCD_COLS; loopVar++) {
    if(str[loopVar] == '\0') {
      break;
    }
    
    bytesPrinted += write(str[loopVar]);
  }
  
  return bytesPrinted;
}

unsigned short int LCDDisplay::write(const char* str, unsigned char size) {
  unsigned char bytesPrinted = 0;
  unsigned char sizeLimit = size;
  
  if(sizeLimit > LCD_COLS) {
    sizeLimit = LCD_COLS;
  }
  
  for(unsigned char loopVar = 0; loopVar < sizeLimit; loopVar++) {
    bytesPrinted += write(str[loopVar]);
  }
  
  return bytesPrinted;
}