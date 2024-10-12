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
#define PULSE_DURATION_ULP32K            8192 // 1/4 second = Ticks from timer when clocked from 32,768Hz low-power oscillator. No prescaler.
#define PULSE_DURATION_HSC               1000
#define PCB_LIGHT_TIMER                  TCD0




/***PCB_LIGHT METHODS***/
void init_PCB_LIGHT() // Initializes PCB light as an output.
{
    PCB_LIGHT_CTRLPORT.DIR |= (1 << PCB_LIGHT_PIN);
}
