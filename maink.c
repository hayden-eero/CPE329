/* Keypad.c: Matrix keypad scanning
 *
 */
 
#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include "LCD.h"
#include "LCD.c"
#include "keypad.h"
#include "keypad.c"
 
void delay(void);
 
int main(void) {
    uint8_t key, rgb;
    int cursorcnt=0;
    char input[19] = {0};
    // setup GPIO for multicolor LED (2.0-2.2) for key bits 2-0
    P2->DIR |= 0x07;    // make pins output
    P2->OUT &= ~0x07;   // turn LED off
 
    P1->DIR |= BIT0;     // use red led for bit key bit 3
    P1->OUT &= ~BIT0;    // turn LED off
 
    keypad_init();      // setup gpio pins for keypad
    LCD_init();
    LCD_command(0x01);
    Write_string_LCD("   Keypad Entry:");
    LCD_Line2();
    delay_us(500000);
 
    while(1) {
        int i =0;
        key = keypad_getkey();  // read the keyboard value
 
        if (key>9 & key!=255){
            if (key==42){
                printToLCD(key);
                key=10;
                cursorcnt++;
                input[cursorcnt-1]='*';
 
                //Used for identifying the array
                for(i=0;i<20;i++){
                    printf("%d ", input[i]);
                }
                printf("\n");
 
                delay_us(400000);
 
                //determining if cursor cnt is over 21
                if  (cursorcnt>=21){
                    over();
                    cursorcnt = 1;
                    printToLCD(key);
                    for(i=0;i<20;i++){
                        input[i]=0;
                    }
                    input[cursorcnt-1]='*';
                    //Used for identifying the array
                    for(i=0;i<20;i++){
                        printf("%d ", input[i]);
                    }
                    printf("\n");
 
                }
            }
 
            else{
                printToLCD(key);
                key=12;
                cursorcnt++;
                input[cursorcnt-1]='#';
                for(i=0;i<20;i++){
                    printf("%d ", input[i]);
                }
                printf("\n");
                delay_us(400000);
 
                if  (cursorcnt>=21){
                    over();
                    cursorcnt = 1;
                    printToLCD(key);
                    for(i=0;i<20;i++){
                        input[i]=0;
                    }
                    input[cursorcnt-1]='#';
                    //Used for identifying the array
                    for(i=0;i<20;i++){
                        printf("%d ", input[i]);
                    }
                    printf("\n");
                }
            }
        }
 
        else{
        if (key!=255){
        printToLCD(key);
        cursorcnt++;
        input[cursorcnt-1]=key;
        for(i=0;i<20;i++){
            printf("%d ", input[i]);
        }
        printf("\n");
        delay_us(400000);
 
        if  (cursorcnt>=21){
            over();
            cursorcnt = 1;
            printToLCD(key);
            for(i=0;i<20;i++){
                input[i]=0;
            }
            input[cursorcnt-1]=key;
            //Used for identifying the array
            for(i=0;i<20;i++){
                printf("%d ", input[i]);
            }
            printf("\n");
        }
        }
        }
        rgb = key & 0x07; // only keep bottom 3 bits
        P2->OUT = (P2->OUT &= ~ 0x07) | rgb;    // zero bottom 3 bits before
                                                // being set by key value
 
        key = (key >> 3); // shift bit 4 to bit 0
        P1->OUT = (P1->OUT &= ~BIT0) | key;   // only set bit 0 wi8 idk th key
    }
}
