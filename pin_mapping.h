#ifndef _PIN_MAPPING_H_
#define _PIN_MAPPING_H_

/* pin connection of lcd display in 8-bit mode.
            _______________________________________________
           |                                               |
           |             16*2 lcd  display                 |
           |                8-bit mode                     |
           |                                               |
           |                                               |
           |                                               |
           |         D7 D6 D5 D4 D3 D2 D1 D0     EN RW RS  |
            -----------------------------------------------
                     |  |  |  |  |  |  |  |      |  |  |
                     |  |  |  |	 |  |  |  |      |  |  |
                     |	|  |  |  |  |  |  |      |  |  |___P2.3
                     |  |  |  |  |  |  |  |      |  |______GND
                     |  |  |  |  |  |  |  |      |_________P2.2
                     |	|  |  |  |  |  |  |
                     |	|  |  |  |  |  |  |
                     |  |  |  |  |  |  |  |________________P0.0
                     |  |  |  |  |  |  |___________________P0.1
                     |  |  |  |  |  |______________________P0.2
                     |  |  |  |  |_________________________P0.3
                     |  |  |  |____________________________P0.4
                     |  |  |_______________________________P0.5
                     |  |__________________________________P0.6
                     |_____________________________________P0.7
										 
*/

#define LCD_EN                  P2_bit.P2_2
#define LCD_RS                  P2_bit.P2_3
#define LCD_DATA                P0

/*
  IIC SDA = P2^0
  IIC SCL = P2^1
*/

#define IIC_SDA                 P2_bit.P2_0
#define IIC_SCL                 P2_bit.P2_1

#endif