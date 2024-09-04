#include "liquid_crystal.h"
#include "ds1307.h"

// function prototyping
void setup(void);
void loop(void);

void setInitialRTCData(void);
void readRTCData(void);
void displayPresentDateTime(void);

// instantiate drivers
LCDDisplay lcd;
RTC_DS1307 rtc;

// global variables
RTCTime presentTime;
RTCDate presentDate;

void main()
{
  setup();
  
  while(true) {
    loop();
  }
}

void setup(void) {
  timerSetup();
  lcd.setup();
  rtc.setup();
  
  // setInitialRTCData(); // uncomment to set initial time
}

void loop(void) {
  lcd.loop();
  
  readRTCData();
  displayPresentDateTime();
}

void setInitialRTCData(void) {
  presentTime.secs = 0;
  presentTime.mins = 48;
  presentTime.hours = 22;
  presentTime.mode = TWENTY_FOUR_HOURS_MODE;
  
  presentDate.date = 21;
  presentDate.month = 3;
  presentDate.year = 24;
  presentDate.day = THURSDAY;
  
  rtc.setTime(presentTime);
  rtc.setDate(presentDate);
}

void readRTCData(void) {
  presentTime = rtc.getTime();
  presentDate = rtc.getDate();
}

void displayPresentDateTime(void) {
  lcd.setCursor(4, 0);
  
  lcd.print(presentTime.hours, 2);
  lcd.print(":");
  lcd.print(presentTime.mins, 2);
  lcd.print(":");
  lcd.print(presentTime.secs, 2);
  
  lcd.setCursor(4, 1);
  lcd.print(presentDate.date, 2);
  lcd.print("/");
  lcd.print(presentDate.month, 2);
  lcd.print("/");
  lcd.print(presentDate.year, 2);
}