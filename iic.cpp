#include "iic.h"

void IIC::setup(void){
  IIC_SDA = 1;
  IIC_SCL = 1;
}

void IIC::start(void){
  IIC_SCL = 1;
  IIC_SDA = 1;
  blockingDelayUS(HALF_BIT_DELAY);
  IIC_SDA = 0;
  blockingDelayUS(HALF_BIT_DELAY);
}

void IIC::restart(void){
  IIC_SCL = 0;
  blockingDelayUS(HALF_BIT_DELAY / 2);
  IIC_SDA = 1;
  blockingDelayUS(HALF_BIT_DELAY / 2);
  IIC_SCL = 1;
  blockingDelayUS(HALF_BIT_DELAY / 2);
  IIC_SDA = 0;
  blockingDelayUS(HALF_BIT_DELAY / 2);
}

void IIC::stop(void){
  IIC_SCL = 0;
  blockingDelayUS(HALF_BIT_DELAY / 2);
  IIC_SDA = 0;
  blockingDelayUS(HALF_BIT_DELAY / 2);
  IIC_SCL = 1;
  blockingDelayUS(HALF_BIT_DELAY / 2);
  IIC_SDA = 1;
  blockingDelayUS(HALF_BIT_DELAY / 2);
}

void IIC::stopTransmission(void){
  IIC_SDA = 0;
  blockingDelayUS(HALF_BIT_DELAY);
  IIC_SDA = 1;
  blockingDelayUS(HALF_BIT_DELAY);
}

unsigned char IIC::writeByte(unsigned char byte) {
  for(unsigned char loopVar = 0; loopVar < 8; loopVar++) {
    IIC_SCL = 0;
    blockingDelayUS(HALF_BIT_DELAY / 2);
    IIC_SDA = ((byte << loopVar) & 0x80) ? 1 : 0;
    blockingDelayUS(HALF_BIT_DELAY / 2);
    IIC_SCL = 1;
    blockingDelayUS(HALF_BIT_DELAY);
  }
  
  IIC_SCL = 0;
  IIC_SDA = 1;
  blockingDelayUS(HALF_BIT_DELAY);
  IIC_SCL = 1;
  blockingDelayUS(HALF_BIT_DELAY);
  
  return static_cast<unsigned char>(IIC_SDA);
}

unsigned char IIC::readByte(void){
  unsigned char receivedBit = 0, rxData = 0;
  
  for(unsigned char loopVar = 0; loopVar < 8; loopVar++){
    IIC_SCL = 0;
    IIC_SDA = 1;
    blockingDelayUS(HALF_BIT_DELAY);
    IIC_SCL = 1;
    blockingDelayUS(HALF_BIT_DELAY / 2);
    
    receivedBit = static_cast<unsigned char>(IIC_SDA);
    rxData = (rxData | (receivedBit << (7 - loopVar)));
    
    blockingDelayUS(HALF_BIT_DELAY / 2);
  }
  
  return rxData;
}

void IIC::sendACK(void){
  IIC_SCL = 0;
  blockingDelayUS(HALF_BIT_DELAY / 2);
  IIC_SDA = 0;
  blockingDelayUS(HALF_BIT_DELAY / 2);
  IIC_SCL = 1;
  blockingDelayUS(HALF_BIT_DELAY);
}

void IIC::sendNACK(void){
  IIC_SCL = 0;
  blockingDelayUS(HALF_BIT_DELAY / 2);
  IIC_SDA = 1;
  blockingDelayUS(HALF_BIT_DELAY / 2);
  IIC_SCL = 1;
  blockingDelayUS(HALF_BIT_DELAY);
}

void IIC::blockingDelayUS(unsigned int delayVal) {
   unsigned int limit = delayVal / 15;

   for(unsigned int loopVar = 0; loopVar < limit; loopVar++) {
     // do nothing
   }
}