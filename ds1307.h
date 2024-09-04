#ifndef _DS1307_H_
#define _DS1307_H_

#include "iic.h"

#define DS1307_IIC_ADDRESS	0xD0

enum RTCTimeMode {
  AM_TIME = 0,
  PM_TIME,
  TWENTY_FOUR_HOURS_MODE
};

enum RTCDay {
  MONDAY = 1,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
  SUNDAY
};

struct RTCTime {
  RTCTimeMode mode;
  unsigned char hours;
  unsigned char mins;
  unsigned char secs;
};

struct RTCDate {
  unsigned char date;
  unsigned char month;
  unsigned char year;
  RTCDay day;
};

class RTC_DS1307 {
public:
  void setup(void);
  
  void setTime(const RTCTime& rtcTimeRef);
  RTCTime getTime(void);
  
  void setDate(const RTCDate& rtcDateRef);
  RTCDate getDate(void);
protected:
  IIC iicDriver;
  
  void writeByte(unsigned char address, unsigned char data);
  unsigned char readByte(unsigned char address);
  
  void writeBytes(unsigned char address, unsigned char* pData,unsigned char noOfBytes);
  void readBytes(unsigned char address, unsigned char* pData,unsigned char noOfBytes);
    
  void delay(unsigned int delayVal);
};

#endif