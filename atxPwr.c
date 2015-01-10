/****************************************************************************
* Project:  Atx delay power on                                              *
*  Author:  Jussi Kinnunen                                                  *
****************************************************************************/

#include <msp430g2211.h>
#include <msp430.h>
#include <legacymsp430.h>

#define LED1      BIT0                     // P1.0 LaunchPad-alustalla
#define PWRSWITCH      BIT6                     // P1.6 LaunchPad-alustalla

#define LED_DIR   P1DIR
#define LED_OUT   P1OUT

#define PWRDELAY 30 

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;              // Stop watchdog-timer
    P1DIR |= LED1 + PWRSWITCH;             
    P1OUT |=  LED1+PWRSWITCH;
   

    unsigned int i;
    unsigned int dummy = 0;
    unsigned int seconds = 0;
    unsigned int minutes = 0;

    while(minutes<PWRDELAY){
    while(seconds<60) {
        P1OUT &= ~(LED1);      
        for (i=0; i<50000; i++) dummy++; 
        P1OUT |= LED1;            
        for (i=0; i<50000; i++) dummy++;   	
	seconds++;
    }
    seconds=0;
    minutes++;
    }

    if (!(BIT3 & P1IN)){
      P1OUT &= ~(PWRSWITCH);
      for (i=0; i<50000; i++) dummy++; 
      for (i=0; i<50000; i++) dummy++; 
      for (i=0; i<50000; i++) dummy++; 
      P1OUT |=  PWRSWITCH;
    }
}
