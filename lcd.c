#include "p24fj64ga002.h"
#include "timer.h"
#include "lcd.h"



#define LCD_DATA   LATB
#define LCD_RS  LATBbits.LATB7
#define LCD_E   LATBbits.LATB6

#define TRIS_D7  TRISBbits.TRISB15
#define TRIS_D6  TRISBbits.TRISB14
#define TRIS_D5  TRISBbits.TRISB13
#define TRIS_D4  TRISBbits.TRISB12
#define TRIS_RS  TRISBbits.TRISB7
#define TRIS_E   TRISBbits.TRISB6

#define LCD_WRITE_DATA    1
#define LCD_WRITE_CONTROL 0

#define LOWER 1
#define UPPER 0


/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATB. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){

    if(lower){
        LATB = (word<<12);
    }
    else{
        LATB = (word >>4)<<12;
    }

    LCD_RS = commandType;
    delayUs(1);
    LCD_E = 1;
    delayUs(1);
    LCD_E = 0;
    delayUs(1);
    delayUs(delayAfter);
}


/*
 * Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){

    writeFourBits(word, commandType, delayAfter, UPPER);  // Upper and lower defined above
    writeFourBits(word, commandType, delayAfter, LOWER);
}


/*
 * Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {

     writeLCD(c, LCD_WRITE_DATA, 46);
}


/*
 * Initialize the LCD
 */
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).

    TRIS_RS = 0;
    TRIS_E = 0;
    TRIS_D7 = 0;
    TRIS_D6 = 0;
    TRIS_D5 = 0;
    TRIS_D4 = 0;

    delayUs(15000);                                         // delayUs(15000);
    writeFourBits(0x03, LCD_WRITE_CONTROL, 4100,  LOWER);   // Writes 000011 and delays 4100Us

    writeFourBits(0x03,LCD_WRITE_CONTROL, 100,  LOWER);     // Writes 000011 and delays 100Us

    writeLCD(0x32,LCD_WRITE_CONTROL,100);   // Good

    writeLCD(0x28,LCD_WRITE_CONTROL,40);    // Enable 4-bit interfac
    writeLCD(0x08,LCD_WRITE_CONTROL,40);    // Function Set (specifies data width = 0, lines = 1, and font.00100
    writeLCD(0x01,LCD_WRITE_CONTROL,1640);  // Clear LCD
    writeLCD(0x06,LCD_WRITE_CONTROL,40);
    writeLCD(0x0C,LCD_WRITE_CONTROL,40);
}


/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {

    int i = 0;
    while (s[i]!= 0){
        printCharLCD(s[i]);
        i = i+1;
    }
}


/*
 * Clear the display.
 */
void clearLCD(){

    writeLCD(0x01,LCD_WRITE_CONTROL,1640);
}


/*
 * Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){

    int pos = 0x80;
    pos = pos + y;

    if (x == 1){
        pos = pos + 0x40;
    }

    writeLCD( pos,LCD_WRITE_CONTROL,40);
    // Need actual command to move the cursor to register 0xpos
}


/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){

    initLCD();
    int i = 0;
    printCharLCD('c');
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
}


 const char*  getTimeString(int F, int FF , int S , int SS, int M , int MM ){

      char* timeString ="00:00:00";
//    timeString[0] = '0' + F;
//    timeString[1] = '0' + FF;
//    timeString[3] = '0' + S;
//    timeString[4] = '0' + SS;
//    timeString[6] = '0' + M;
//    timeString[7] = '0'+ MM;

    timeString[0] = (char) F;
    timeString[1] = (char) FF;
    timeString[3] = (char) S;
    timeString[4] = (char) SS;
    timeString[6] = (char) M;
    timeString[7] = (char) MM;

    printStringLCD(timeString);

    return timeString;
}


void printTime(int F, int FF , int S , int SS, int M , int MM ){

    printCharLCD('0' + MM);
    printCharLCD('0' + M);
    printCharLCD(':');
    printCharLCD('0' + SS);
    printCharLCD('0' + S);
    printCharLCD(':');
    printCharLCD('0' + FF);
    printCharLCD('0' + F);
 }

