/*
 *  TIMER_A Demo program
 *
 *  ACLK = TACLK = 32kHz, MCLK = SMCLK = default DCO ~3MHz
 *
 *  TIMER_A0 utilize ACLK - TA0CLK = 32768Hz
 *  TIMER_A0 CCR0 and CCR1 to create 2 timing events
 *  TIMER_A0 -> CCR[0] = 32768 = 0.5 Hz
 *  TIMER_A0 -> CCR[1] = 16384 = 0.5 Hz with 0.5s offset from CCR0
 */

#include "msp.h"
#include "delay.h"
int counting=0;
int set=4;
void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    set_DCO(FREQ_1_5_Mhz);
     //GPIO
    P2->SEL1&= ~BIT0;
    P2->SEL0 &= ~BIT0;

       // setup LEDs
    P2->DIR |= BIT0;


    P2->OUT &= ~BIT0;

    // setup TIMER_A0
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; // clear interrupt


    TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled


    TIMER_A0->CCR[0] = 46875-1;


    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 |TIMER_A_CTL_ID__8| TIMER_A_CTL_MC_1; // SMCLK, UP mode

    TIMER_A0->EX0= TIMER_A_EX0_TAIDEX_7  ;
    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);   // set NVIC interrupt


    __enable_irq();     // Enable global interrupt

    while(1);

}




void TA0_0_IRQHandler(void) {

    if (counting==set){
        printf("TOGGLING!\n");
        P2->OUT^=BIT0;
        counting=0;
    }
    else{
        counting++;

    }
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;  // Clear the CCR0 interrupt


}
