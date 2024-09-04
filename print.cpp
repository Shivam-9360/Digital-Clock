#include "print.h"

unsigned short int Print::print(const char character) {
  return write(character);
}

unsigned short int Print::print(const char* str) {
  return write(str);
}

unsigned short int Print::print(unsigned char number, unsigned char digits) {
  return print(static_cast<unsigned long>(number), digits);
}

unsigned short int Print::print(unsigned short number, unsigned char digits) {
  return print(static_cast<unsigned long>(number), digits);
}

unsigned short int Print::print(signed char number, unsigned char digits) {
  return print(static_cast<signed long>(number), digits);
}

unsigned short int Print::print(signed short number, unsigned char digits) {
  return print(static_cast<signed long>(number), digits);
}

unsigned short int Print::print(signed long number, unsigned char digits) {
  unsigned short int totalCharsPrinted = 0;
  
  if(number >= 0) {
    return print(static_cast<unsigned long>(number), digits);
  } else {
    totalCharsPrinted += write('-');
    totalCharsPrinted += print(static_cast<unsigned long>(number), digits);
    
    return totalCharsPrinted;
  }
}

unsigned short int Print::print(unsigned long number, unsigned char digits) {
  char buf[11]; // largest number requires 10 bytes + null terminator
  char* str = &buf[sizeof(buf) - 1];
  
  unsigned long n = number;
  
  *str = '\0';
  
  do {
    char c = n % 10;
    n /= 10;
    
    *--str = c + '0';
    digits = digits > 0 ? (digits - 1) : 0;
  } while (n > 0);

  while (digits > 0) {
    *--str = '0';
    digits--;
  }
  
  return write(str);
}