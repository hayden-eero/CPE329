#include "msp.h"
#include "delay.h"
 
void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; 	// stop watchdog timer
 
	  set_DCO(FREQ_1_5_Mhz);
 	  //GPIO
	  P4->SEL1&= ~(BIT1|BIT0);
	  P4->SEL0 &= ~(BIT1|BIT0);
 
   	// setup LEDs
	  P4->DIR |= BIT0;
	  P4->DIR |= BIT1;
 
	  P4->OUT &= BIT0;
	  P4->OUT &= BIT1;
	  // setup TIMER_A0
	  TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; // clear interrupt
	  TIMER_A0->CCTL[1] &= ~TIMER_A_CCTLN_CCIFG; // clear interrupt
 
	  TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled
	  TIMER_A0->CCTL[1] = TIMER_A_CCTLN_CCIE; // TACCR1 interrupt enabled
 
	  TIMER_A0->CCR[0] = 1500-1;
	  TIMER_A0->CCR[1] =750-1 ;
 
	  TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_ID_0|TIMER_A_CTL_MC_1|TIMER_A_CTL_CLR; // SMCLK, UP mode
 
	  NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);   // set NVIC interrupt
	  NVIC->ISER[0] = 1 << ((TA0_N_IRQn) & 31);   // TA0_0 and TA0_N
 
	  __enable_irq(); 	// Enable global interrupt
 
    while(1);
 
}
// Timer A0_0 interrupt service routine
void TA0_0_IRQHandler(void){
    TIMER_A0->CCTL[1] &= ~TIMER_A_CCTLN_CCIFG; // clear both interrupts
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; 
    P4->OUT ^= BIT0;                                                              // toggle both 
    P4->OUT^=BIT1;
}
// Timer A0_N interrupt service routine for CCR1 - CCR4
void TA0_N_IRQHandler(void){
    if(TIMER_A0->CCTL[1]&TIMER_A_CCTLN_CCIFG){   // check for CCR1 interrupt
        TIMER_A0->CCTL[1] &= ~TIMER_A_CCTLN_CCIFG;  // Clear the CCR0 interrupt
    }
    P4->OUT ^= BIT0;
}
