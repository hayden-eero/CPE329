/* Keypad.c: Matrix keypad scanning
*
*/
#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include "LCD.h"
#include "keypad.h"
#include "LCD.c"
#include "keypad.c"
void delay(void);
int main(void) {
    uint8_t key, rgb;

    // setup GPIO for multicolor LED (2.0-2.2) for key bits 2-0
    P2->DIR |= 0x07;    // make pins output
    P2->OUT &= ~0x07;   // turn LED off

    P1->DIR |= BIT0;     // use red led for bit key bit 3
    P1->OUT &= ~BIT0;    // turn LED off

    keypad_init();      // setup gpio pins for keypad
    LCD_init();
    while(1) {
        key = keypad_getkey();  // read the keyboard value

        if (key>9 & key!=255){ //check if the input is either nothing and greater than 9
            if (key==42){      // using ascii value to determine if '*' is the input

                printf("%c\n", key);  //printing key value to console
                printToLCD(key);  //printing to the LCD

                key=10; //key value 
            }
            else{
                printf("%c\n",key);
                printToLCD(key);    //printing '#' on the LCD
                key=12;
            }

        }
        else{
        printf("%d\n",key);     // print key value to console
        if (key!=255){
        printToLCD(key);
        }
        }

        rgb = key & 0x07; // only keep bottom 3 bits
        P2->OUT = (P2->OUT &= ~ 0x07) | rgb;    // zero bottom 3 bits before
                                                // being set by key value

        key = (key >> 3); // shift bit 4 to bit 0
        P1->OUT = (P1->OUT &= ~BIT0) | key;   // only set bit 0 wi8 idk th key
    }
}
