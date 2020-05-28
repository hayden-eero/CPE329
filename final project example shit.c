/* UART2 echo
 *
 * Pin header J34 is connected to UART2.
 * Pin 2 - Tx (P3.3)
 * Pin 3 - Rx (P3.2)
 * The UART2 is configure for 115200 Baud 8-N-1.
 * Connect a USB to 3.3V serial converter to a PC and launch a
 * terminal emulator on the PC. The keyboard input will be sent
 * by the terminal emulator to USB-serial converter. Connect the
 * Tx pin of the converter to the Rx (pin 3 of J34). This program
 * echoes back the characters to the Tx (pin 2 of J34). Connect Tx
 * of J34 to Rx of the USB-Serial converter and the character will
 * appear on the terminal emulator window.
 *
 * Built and tested with MSP432P401R Rev. C, Keil MDK-ARM v5.24a and MSP432P4xx_DFP v3.1.0
 */
/*
#include "msp.h"

void UART2init(void);
void UART2Tx(char c);
unsigned char UART2Rx(void);
void delayMs(int n);

int main(void) {
    char c;

    UART2init();
    delayMs(1);             // wait for output line to stabilize

    UART2Tx('>');           // send prompt

    for(;;) {
        c = UART2Rx();
        if (c == '\r')
            UART2Tx('\n');
        UART2Tx(c);
    }
}

void UART2init(void) {
    EUSCI_A2->CTLW0 |= 1;       // put in reset mode for config
    EUSCI_A2->MCTLW = 0;        // disable oversampling
    EUSCI_A2->CTLW0 = 0x0081;   // 1 stop bit, no parity, SMCLK, 8-bit data
    EUSCI_A2->BRW = 26;         // 3000000 / 115200 = 26
    P3->SEL0 |= 0x0C;           // P1.3, P1.2 for UART
    P3->SEL1 &= ~0x0C;
    EUSCI_A2->CTLW0 &= ~1;      // take UART out of reset mode
}

void UART2Tx(char c) {
    while(!(EUSCI_A2->IFG & 0x02)) { }  // wait for transmit buffer empty
    EUSCI_A2->TXBUF = c;                // send a char
}

unsigned char UART2Rx(void){
    char c;

    while(!(EUSCI_A2->IFG & 0x01)) { }    // wait until receive buffer is full
    c = EUSCI_A2->RXBUF;                  // read the receive char
    return c;
}

// system clock at 3 MHz
void delayMs(int n) {
    int i, j;
    for (j = 0; j < n; j++)
        for (i = 750; i > 0; i--);      // Delay
}
*/
