#include "msp.h"
#include "DAC.h"

char data[5];
int flag;
char receivedMSPChar;

//This function converts the string that is input on the TeraTerm Window
//to an integer that can be sent out to the DAC
int string_to_int(char string[]){
    int i = 0;
    int data = 0;

    for (i = 0; i < 4; i++){
        if (string[i] != '\0'){
            data *= 10;
            data += string[i] - 48;
        }
        else
            break;
    }
    printf("Data:%d\n",data);
    return data;
}

int main(void)
{
    //Initializing the DAC
    startDAC();

    // Stop watchdog timer
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    // Configure UART pins
    // set 2-UART pin as secondary function
    P1->SEL0 |= BIT2 | BIT3;

    // Configure UART
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;      // Put eUSCI in reset
    EUSCI_A0->CTLW0 =  EUSCI_A_CTLW0_SWRST |     // Remain eUSCI in reset
                       EUSCI_B_CTLW0_SSEL__SMCLK;// Configure eUSCI clock source for SMCLK

    // Baud Rate calculation
    // 3000000/(115200) = 26.041667
    // Fractional portion = 0.041667
    // User's Guide Table 21-4: UCBRSx = 0x00
    // UCBRx = int (26.041667 / 16) = 1
    // UCBRFx = int (((26.041667/16)-1)*16) = 10

    EUSCI_A0->BRW = 1;                      // Using baud rate calculator
    EUSCI_A0->MCTLW = (10 << EUSCI_A_MCTLW_BRF_OFS) | EUSCI_A_MCTLW_OS16;
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Initialize eUSCI
    EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;    // Clear eUSCI RX interrupt flag
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE;        // Enable USCI_A0 RX interrupt

    // Enable global interrupt
    __enable_irq();

    // Enable eUSCIA0 interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31);
    receivedMSPChar=0;
    int i=0;
    while(1){ 
        //In this while function, it constantly sends out the data to the DAC
        if(flag){
            //This statement checks if the user put more than 4 numbers in
            if ((receivedMSPChar>47 && receivedMSPChar<58)){
                data[i]= receivedMSPChar;
                i+=1;
                if (i>4){
                    printf("Too many Characters\n");
                    break;
                }
                EUSCI_A0->TXBUF = EUSCI_A0->RXBUF;
                while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));
            }
            //If the number of numbers equal 4 for less then output the data to the DAC
            else if (receivedMSPChar==13){
                int count=0;
                i=0;
                for(count=0; count<i; count++){
                    printf("%d", data[count]);
                }
                data[4] = '\0';
                dataDAC(string_to_int(data));
            }
            //Set flag to 0
            flag=0;
        }
    }
}
// UART interrupt service routine
void EUSCIA0_IRQHandler(void){
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG){        // if interrupt flag is interrrupted due to receive

        // Check if the TX buffer is empty first
        while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));
        //Set RX buffer to 0 and flag to 1
        receivedMSPChar= EUSCI_A0->RXBUF;
        EUSCI_A0->IFG&=~EUSCI_A_IFG_RXIFG;
        flag = 1;
    }
}
