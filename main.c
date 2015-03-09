#include "p24FJ64GA002.h"
#include "timer.h"
#include "keypad.h"
#include "lcd.h"


#define DEBOUNCE_DELAY 10000
#define ENTER "Enter:"
#define SET_MODE "Set Mode:"
#define GOOD "Good"
#define BAD "Bad"
#define VALID "Valid"
#define INVALID "Invalid"


typedef enum stateTypeEnum{
    enterPrint,waitForPress, debouncePress, scanButton, waitForRelease, debounceRelease,setModeScanButton, printSetMode
} stateType;

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

/***********************************************************
* waitForPress - this state will wait for the ISR to go high
* debouncePress - this state runs of the timer for some delay
* scanButton - runs the keypad scan function to find which button was pressed and sends that to LCD
* waitForRelease - waits till ISR goes high again and sets its direction
* debounceRelease - delay for debouncing of button
***********************************************************/

volatile stateType curState = enterPrint;


int main(void){
    initKeypad();
    initLCD();
    
    
   
    int doubleStarCheck = 0;
    int invalid = 0;
    int checkInvalid = 0;
    int inSetMode = 0;
    int validCheck = 0;

    IEC1bits.CNIE = 1; //Overall Change Notification on
    IFS1bits.CNIF = 0; //Set the flag down





    char key = -1;

    while(1){
        switch(curState){
            case enterPrint:
                //Act as initial Enter state
                clearLCD();
                moveCursorLCD(0,0);
                printStringLCD(ENTER);
                moveCursorLCD(1,0);
                curState = waitForPress;
                break;
            case waitForPress:
                break;
                
            case debouncePress:
                delayUs(DEBOUNCE_DELAY);
                if(inSetMode == 0){
                curState = scanButton;
                }
                else{
                    
                    curState = setModeScanButton;
                }
                break;
                
            case scanButton:
                key = scanKeypad();
                doubleStarCheck = checkStar(key,doubleStarCheck);
                printCharLCD(key);
                resetKeypad();
                IEC1bits.CNIE = 1;
                if(doubleStarCheck == 2){
                    clearLCD();
                    moveCursorLCD(0,0);
                    printStringLCD(SET_MODE);
                    moveCursorLCD(1,0);
                    inSetMode = 1;
                    
                }
                else{

                    inSetMode = 0;
                
                
                }
                curState = waitForRelease;
                break;
                
            case waitForRelease:
                break;
                
            case debounceRelease:
                delayUs(DEBOUNCE_DELAY);
                curState = waitForPress;
                break;

           
            case setModeScanButton:
                key = scanKeypad();
                checkInvalid = checkValid(key);
                printCharLCD(key);
                resetKeypad();
                IEC1bits.CNIE = 1;
                if(checkInvalid == 0){
                    //Invalid Condition
                    clearLCD();
                    moveCursorLCD(0,0);
                    printStringLCD(INVALID);
                    delayUs(20000);
                    curState = enterPrint;
                    

                }
                else{

                  curState = waitForRelease;

                }
                
                break;
              default:

                break;         
            }
            
    }
    return 0;
}

void _ISR _CNInterrupt(void){

    IFS1bits.CNIF = 0;
    if(COL1 == KEY_PRESSED || COL2 == KEY_PRESSED || COL3 == KEY_PRESSED)curState = debouncePress;
    else curState = debounceRelease;
}
