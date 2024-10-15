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
int TOGGLE_PCB_LIGHT_FLAG = 0;
#define PULSE_DURATION_PCB_LIGHT 250 // Defines how long, in milliseconds, PCB_LIGHT stays on when toggled.



/***PCB_LIGHT METHODS***/
void init_PCB_LIGHT() // Initializes PCB light as an output.
{
    PCB_LIGHT_CTRLPORT.DIR |= (1 << PCB_LIGHT_PIN);
}

void enable_PCB_LIGHT()
{
   PCB_LIGHT_CTRLPORT.OUT |= (1 << PCB_LIGHT_PIN); 
}

void disable_PCB_LIGHT()
{
    PCB_LIGHT_CTRLPORT.OUT &= ~(1 << PCB_LIGHT_PIN);
}

int finishPCBtoggle(void)
{
    disable_PCB_LIGHT();
    return 0;
}