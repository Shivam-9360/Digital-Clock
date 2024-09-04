#include "ds1307.h"

void RTC_DS1307::setup(void) {
  iicDriver.setup();
}

void RTC_DS1307::setTime(const RTCTime& rtcTimeRef) {
  unsigned char pRTCArray[3];
  
  // convert to BCD
  pRTCArray[0] = (((unsigned char)(rtcTimeRef.secs / 10)) << 4) | ((unsigned char)(rtcTimeRef.secs % 10));
  pRTCArray[1] = (((unsigned char)(rtcTimeRef.mins / 10)) << 4) | ((unsigned char)(rtcTimeRef.mins % 10));
  pRTCArray[2] = (((unsigned char)(rtcTimeRef.hours / 10)) << 4) | ((unsigned char)(rtcTimeRef.hours % 10));
  
  switch(rtcTimeRef.mode) {
    case AM_TIME: {
      pRTCArray[2] |= 0x40;
    } break;
    
    case PM_TIME: {
      pRTCArray[2] |= 0x60;
    } break;
    
    case TWENTY_FOUR_HOURS_MODE: {
      // do nothing
    } break;
    
    default: {
      // do nothing
    } break;
  }
  
  writeBytes(0x00, pRTCArray, 3);
}

RTCTime RTC_DS1307::getTime(void) {
  unsigned char pRTCArray[3];
  RTCTime rtcTime;
  
  // read from RTC
  readBytes(0x00, pRTCArray, 3);
  
  // convert from BCD to number
  rtcTime.secs = ((pRTCArray[0] & 0x7F) >> 4) * 10 + (pRTCArray[0] & 0x0F);
  rtcTime.mins = ((pRTCArray[1]) >> 4) * 10 + (pRTCArray[1] & 0x0F);
  
  // if 12 hours mode
  if(pRTCArray[2] & 0x40) {
    // if PM Time
    if(pRTCArray[2] & 0x20) {
      rtcTime.mode = PM_TIME;
    } else {
      rtcTime.mode = AM_TIME;
    }
    
    rtcTime.hours = ((pRTCArray[2] & 0x1F) >> 4) * 10 + (pRTCArray[2] & 0x0F);
  } else {
    rtcTime.mode = TWENTY_FOUR_HOURS_MODE;
    rtcTime.hours = (pRTCArray[2] >> 4) * 10 + (pRTCArray[2] & 0x0F);
  }
  
  return rtcTime;
}

void RTC_DS1307::setDate(const RTCDate& rtcDateRef) {
  unsigned char pRTCArray[4];
  
  // convert to BCD
  pRTCArray[0] = (((unsigned char)(rtcDateRef.day / 10)) << 4) | ((unsigned char)(rtcDateRef.day % 10));
  pRTCArray[1] = (((unsigned char)(rtcDateRef.date / 10)) << 4) | ((unsigned char)(rtcDateRef.date % 10));
  pRTCArray[2] = (((unsigned char)(rtcDateRef.month / 10)) << 4) | ((unsigned char)(rtcDateRef.month % 10));
  pRTCArray[3] = (((unsigned char)(rtcDateRef.year / 10)) << 4) | ((unsigned char)(rtcDateRef.year % 10));

  writeBytes(0x03, pRTCArray, 4);
}

RTCDate RTC_DS1307::getDate(void) {
  unsigned char pRTCArray[4];
  RTCDate rtcDate;
  
  // read from RTC
  readBytes(0x03, pRTCArray, 4);
  
  switch(pRTCArray[0]) {
    case 1: {
      rtcDate.day = MONDAY;
    } break;
    
    case 2: {
      rtcDate.day = TUESDAY;
    } break;

    case 3: {
      rtcDate.day = WEDNESDAY;
    } break;

    case 4: {
      rtcDate.day = THURSDAY;
    } break;

    case 5: {
      rtcDate.day = FRIDAY;
    } break;

    case 6: {
      rtcDate.day = SATURDAY;
    } break;

    case 7: {
      rtcDate.day = SUNDAY;
    } break;

    default: {
      // do nothing
    } break;
  }
  
  rtcDate.date = (pRTCArray[1] >> 4) * 10 + (pRTCArray[1] & 0x0F);
  rtcDate.month = (pRTCArray[2] >> 4) * 10 + (pRTCArray[2] & 0x0F);
  rtcDate.year = (pRTCArray[3] >> 4) * 10 + (pRTCArray[3] & 0x0F);

  return rtcDate;
}

void RTC_DS1307::writeByte(unsigned char address, unsigned char data) {
  iicDriver.start();
  
  // wait until device is free
  while(iicDriver.writeByte(DS1307_IIC_ADDRESS + 0) == 1) {
    iicDriver.start();	
  }	

  iicDriver.writeByte(address);							
  iicDriver.writeByte(data);							
  iicDriver.stop();						
  
}
unsigned char RTC_DS1307::readByte(unsigned char address) {
  unsigned char data = 0;

  iicDriver.start();

  // wait until device is free
  while(iicDriver.writeByte(DS1307_IIC_ADDRESS + 0) == 1) {
    iicDriver.start();	
  }			

  iicDriver.writeByte(address);	
  iicDriver.restart();

  // send i2c address with read command	
  iicDriver.writeByte(DS1307_IIC_ADDRESS + 1);

  data = iicDriver.readByte();

  // make SCK low, so that slave can stop driving SDA pin
  // send a NACK to indiacate single byte read is complete
  iicDriver.sendNACK();

  // send start bit and then stop bit to stop transmission
  iicDriver.stopTransmission();

  return data;
}

void RTC_DS1307::writeBytes(unsigned char address, unsigned char* pData,unsigned char noOfBytes) {
  iicDriver.start();

  // wait until device is free
  while(iicDriver.writeByte(DS1307_IIC_ADDRESS + 0) == 1) {
    iicDriver.start();	
  }		

  iicDriver.writeByte(address);	

  for(unsigned char loopVar = 0; loopVar < noOfBytes; loopVar++) {
    iicDriver.writeByte(pData[loopVar]);
  }

  iicDriver.stop();
}

void RTC_DS1307::readBytes(unsigned char address, unsigned char* pData,unsigned char noOfBytes) {
  iicDriver.start();

  // wait until device is free
  while(iicDriver.writeByte(DS1307_IIC_ADDRESS + 0) == 1) {
    iicDriver.start();	
  }	

  iicDriver.writeByte(address);	
  iicDriver.restart();

  // send i2c address with read command	
  iicDriver.writeByte(DS1307_IIC_ADDRESS + 1);		

  pData[0] = iicDriver.readByte();

  for(unsigned char loopVar = 1; loopVar < noOfBytes; loopVar++) {		
    iicDriver.sendACK();
    pData[loopVar] = iicDriver.readByte();
  }

  // make SCK low, so that slave can stop driving SDA pin
  // send a NACK to indiacate single byte read is complete
  iicDriver.sendNACK();
        
  // send start bit and then stop bit to stop transmission
  iicDriver.stopTransmission();
}

void RTC_DS1307::delay(unsigned int delayVal) {
  for(unsigned int loopVar = 0; loopVar < delayVal; loopVar++) {
    // do nothing
  }
}