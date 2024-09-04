#ifndef _IIC_H_
#define _IIC_H_

#include "pin_mapping.h"
#include "timer.h"

// iic speed settings
#define IIC_SPEED_FACTOR	          1		
#define HALF_BIT_DELAY                   ((500 * (FREQ_OSC / 12000000)) / (IIC_SPEED_FACTOR))

class IIC {
public:
  void setup(void);
  
  void start(void);
  void restart(void);
  void stop(void);
  
  void sendACK(void);
  void sendNACK(void);
  
  void stopTransmission(void);
  
  unsigned char writeByte(unsigned char byte);
  unsigned char readByte(void);

protected:
  void blockingDelayUS(unsigned int delayVal);
};

#endif