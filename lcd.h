/* 
 * File:   lcd.h
 * Author: Anthony
 *
 * Created on March 6, 2015, 11:54 AM
 */

#ifndef LCD_H
#define	LCD_H

// I need all my defines

void writeLCD(unsigned char word, unsigned int commandType, unsigned int delay);
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower);
void initLCD(void);
void clearLCD(void);
void moveCursorLCD(unsigned char x, unsigned char y);
void printCharLCD(char c);
void printStringLCD(const char* s);
void printTime(int F, int FF , int S , int SS, int M , int MM );
void testLCD();
const char* getTimeString(int F, int FF , int S , int SS, int M , int MM );


#endif	/* LCD_H */

