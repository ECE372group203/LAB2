/**************************************************************************************************/
//
// Author	Eric Moser
// Course	ECE372a
// Date		13 March 2015
// File		keypad.h
//
// Description:
//
//
/**************************************************************************************************/


#ifndef KEYPAD_H
#define KEYPAD_H

#define ROW1_TRI TRISAbits.TRISA0
#define ROW2_TRI TRISAbits.TRISA1
#define ROW3_TRI TRISBbits.TRISB2
#define ROW4_TRI TRISBbits.TRISB3

#define COL3_TRI TRISBbits.TRISB5
#define COL1_TRI TRISBbits.TRISB11
#define COL2_TRI TRISBbits.TRISB10

#define ROW1 LATAbits.LATA0
#define ROW2 LATAbits.LATA1
#define ROW3 LATBbits.LATB2
#define ROW4 LATBbits.LATB3

#define COL3 PORTBbits.RB5
#define COL1 PORTBbits.RB11
#define COL2 PORTBbits.RB10

#define ROW1_ODC ODCAbits.ODA0
#define ROW2_ODC ODCAbits.ODA1
#define ROW3_ODC ODCBbits.ODB2
#define ROW4_ODC ODCBbits.ODB3

#define COL3_INE CNEN2bits.CN27IE
#define COL1_INE CNEN1bits.CN15IE
#define COL2_INE CNEN2bits.CN16IE

#define COL3_PU CNPU2bits.CN27PUE
#define COL1_PU CNPU1bits.CN15PUE
#define COL2_PU CNPU2bits.CN16PUE

#define ON 1
#define OFF 0

#define KEY_PRESSED 0
#define KEY_RELEASED 1


void initKeypad(void);
char scanKeypad(void);
void setRows(unsigned int row);
int checkStar(char key, int start);
int checkValid(char key);

#endif // KEYPAD_H