/* 
 * File:   pcbLight.h
 * Author: Leonard
 *
 * Created on October 12, 2024, 8:48 AM
 */

#ifndef PCBLIGHT_H
#define	PCBLIGHT_H
#endif




/***PCB_LIGHT APP DEPENDENCIES***/
#include <avr/io.h>




/***PCB_LIGHT HARDWARE DEFINITIONS***/
#define PCB_LIGHT_PIN           0 // Digital pin for output.
#define PCB_LIGHT_CTRLPORT      PORTA // MCU port for GPIO control.




/***PCB_LIGHT CONTROL DEFINITIONS***/
#define PCB_LIGHT_TIMER                  TCB0
uint16_t pulseDur_PCB_LIGHT; // Defines how long PCB_LIGHT stays on when toggled.
uint32_t timerFreq_PCB_LIGHT;
int PCBLIGHT_TIMERFREQ_CHNG_FLAG = 0; // Used by system controller to indicate when the system clock frequency has changed. This record helps prevent specific timing functions from having to run through a look up table when the frequency is not changing



/***PCB_LIGHT METHODS***/
void init_PCB_LIGHT(uint32_t timerFreq) // Initializes PCB light as an output.
{
    PCB_LIGHT_CTRLPORT.DIR |= (1 << PCB_LIGHT_PIN);
    timerFreq_PCB_LIGHT = timerFreq;
}




/***PCB_LIGHT TIMING METHODS***/
void configTimer_blink_PCB_LIGHT()
{
    
    PCB_LIGHT_TIMER.CTRLA |= (1 << TCB0_CLKSEL0); // clock-per set as clock source.
    PCB_LIGHT_TIMER.CTRLA |= (1 << TCB0_RUNSTNDBY); // Allow TCB0 to run in STANDBY.
    
    if(PCBLIGHT_TIMERFREQ_CHNG_FLAG) // System clock has changed frequency, which effects value needed to be written to comparative data-structures.
    {
        
        switch(timerFreq_PCB_LIGHT)
        {
            case 32768:
            {

            }
            case 12000000:
            {

            }
            case 6000000:
            {

            }
            case 1500000:
            {

            }
            case 750000:
            {

            }
            case 375000:
            {

            }
            case 4000000:
            {

            }
            case 2400000:
            {

            }
            case 2000000:
            {

            }
            case 1000000:
            {

            }
            case 500000:
            {

            }
        }
        
    }
    else // You can use last value of pulseDur_PCB_LIGHT.
    {
        
    }
    
    PCB_LIGHT_TIMER.CTRLA |= (1 << TCD0_ENABLE);
}