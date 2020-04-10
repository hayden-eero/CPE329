/**
 * main.c
 */
#include "msp.h"
#include "delay.h"

/*
const int FREQ_1_5_Mhz=1.5;
const int FREQ_3_Mhz= 3;
const int FREQ_6_Mhz= 6;
const int FREQ_12_Mhz= 12;
const int FREQ_24_Mhz=24;
const int FREQ_48_Mhz=48;


void delay_ms(int time, int freq){


    //set_DCO(freq); assume DCO is suppplying the MCLK frequency
    set_DCO(freq);
    int k;
    int clock;
    if (freq==1.5){
    clock=time/16;
    }
    else if (freq==3){
        clock=time/8;
    }
    else if (freq==6){
        clock = time/4;
    }
    else if (freq==12){
        clock =time/2;
    }
    else if (freq==24){
        clock =time;
    }
    else if (freq ==48){
        clock=2*time;
    }


    for (k=clock; k>0; k--){


        P1->OUT^=0xFF;

    }


    P1->OUT&=0x00;
    for (clock =8; clock>0; clock--){}

}


void find_ratio(int time, int freq){
    int k;
    set_DCO(freq);
     int j=0;

     for (time; time>0; time--){


        P1->OUT^=0xFF;

     }

     P1->OUT&=0x00;

     for (time =8; time>0; time--){}
 }
*/

void main(void)
    {
    int i=0;
    int LEDcounter=0;
    int counter=0;

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
                            //Port to start designating LED Blink (I need Pin 1.0 and 2.0,2.1,2.2 for LED blinking)
        P1->SEL0 &= ~BIT0;  //designate pin 1.0 as a GPIO
        P1->SEL1 &= ~BIT0;   //
        /*P1->DIR|= 0x01;*/
        P1->DIR|=BIT0;     // make pin 1.0 into a output

        P2-> SEL1 &= (~BIT2)|(~BIT1)|(~BIT0);  // make pin GPIO
        P2-> SEL0 &= (~BIT2)|(~BIT1)|(~BIT0);

        P2->DIR |= 0x07;


        P1->OUT&=0x00;


        P1-> SEL0 &= ~BIT5;
        P1->SEL1 &= ~BIT5;
        P1-> DIR|= BIT5;
        P1->OUT|=BIT5;    // turn on output pin 1.5 and the previous turned on 1.0

        P4-> SEL0 |=BIT3;
             P4->SEL1 &= ~BIT3;
             P4-> DIR|= BIT3;
        while(1)
        {

            // LED code
            P1->OUT&=~BIT5;
            switch (LEDcounter%3)
                {
                    case 0:
                                P2->OUT|= BIT0;
                                P2->OUT &= ~BIT1;
                                P2->OUT &= ~BIT2;
                                LEDcounter++;
                                break;
                    case 1:
                                P2->OUT&= ~BIT0;
                                P2->OUT |= BIT1;
                                P2->OUT &= ~BIT2;
                                LEDcounter++;
                                break;

                    case 2:
                                P2->OUT&= ~BIT0;
                                P2->OUT |= ~BIT1;
                                P2->OUT &= BIT2;

                                LEDcounter=0;
                                break;
                  }


            P1->OUT^=BIT0;
            for (i=0; i<100000; i++);




        /*set_DCO(6000000);*/

            // callling delay*/
        counter= delay_us(500,24000000);
        printf("%d", counter);
        //executing the delay
        for (i=counter; i>0; i--){


               P1->OUT^=BIT5;

           }


           P1->OUT&=~BIT5;
           for (counter=8; counter>0; counter--){}

        /*find_ratio(130,1.5);*/
        }

    }

        /*
        int freq=3;
        if (freq==48){
            freq48();
        }
        else{
        set_DCO(freq);
        }


        delay_us(10us);

            /*
          if ( CS->STAT & 0x00000001 ==1){
              printf("bruh\n");
          }

         /*CS->CLKEN|=0x00000002;
          if (CS->STAT & 0x00020000){
              printf("tfshit\n");
          }


}

*/
