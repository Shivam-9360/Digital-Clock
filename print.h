#ifndef _PRINT_H_
#define _PRINT_H_

class Print {
public:
  // print string / characters
  unsigned short int print(const char character);
  unsigned short int print(const char* str);
  
  // print numbers
  unsigned short int print(unsigned char number, unsigned char digits = 2);
  unsigned short int print(unsigned short number, unsigned char digits = 2);
  unsigned short int print(unsigned long number, unsigned char digits = 2);
  
  unsigned short int print(signed char number, unsigned char digits = 2);
  unsigned short int print(signed short number, unsigned char digits = 2);
  unsigned short int print(signed long number, unsigned char digits = 2);
  
protected:
  // write interface
  virtual unsigned short int write(char character) = 0;
  virtual unsigned short int write(const char* str) = 0;
  virtual unsigned short int write(const char* str, unsigned char size) = 0;
};

#endif