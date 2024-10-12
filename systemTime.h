



/***REALTIME & CALENDAR APP DEPENDENCIES***/
#include "realTime_config.h"




/***SYSTEM TIME STRUCTURE***/
struct time
{
    uint16_t milliseconds;
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;
    int leapYear;
};




/***SYSTEM TIMING VARIABLES***/
struct time sysTime;




/***REALTIME KEEPING METHODS***/
/*
* This method updates the system time, and ensures that the PCB light is blinked every second.
*/
void update_time(int increment)
{
    
    // Determine increment method:
    if(increment == MILLIS)
    {
        sysTime.milliseconds += 1;
        
        if(sysTime.milliseconds == 1000)
        {
            sysTime.seconds += 1;
            sysTime.milliseconds = 0;
            init_PCB_LIGHT_toggle();
            
            if(sysTime.seconds == 60)
            {
                sysTime.minutes += 1;
                sysTime.seconds = 0;
                
                if(sysTime.minutes == 60)
                {
                    sysTime.minutes = 0;
                     sysTime.hour += 1;
                    
                    if(sysTime.hour == 24)
                    {
                        
                        sysTime.hour = 0;
                        sysTime.day += 1;
                        
                        // Determine month to process month rollover:
                        if(sysTime.day == 29)
                        {
                            
                            if(sysTime.month == FEBRUARY)
                            {
                                if(!sysTime.leapYear))
                                 {
                                    
                                    sysTime.month += 1;
                                    sysTime.day = 0;
                                    
                                    if(sysTime.month == 13)
                                    {
                                        sysTime.month = 1;
                                        if(isLeapYear(sysTime.year))
                                        {
                                            sysTime.leapYear = 1;
                                        }
                                        
                                    }
                                    
                                 }
                            }
                            
                         }
                          else if(sysTime.day == 30)
                          {
                            
                            if(sysTime.month == FEBRUARY)
                            {
                                sysTime.month += 1;
                                sysTime.day = 0;
                                
                                if(sysTime.month == 13)
                                {
                                    sysTime.month = 1;
                                    if(isLeapYear(sysTime.year))
                                    {
                                        sysTime.leapYear = 1;
                                    }
                                        
                                }
                                
                            }
                            
                          }
                          else if(sysTime.day == 31)
                          {
                            
                            if(is30dayMonth(sysTime.month))
                            {
                                sysTime.month += 1;
                                sysTime.day = 0;
                                
                                if(sysTime.month == 13)
                                {
                                    sysTime.month = 1;
                                    if(isLeapYear(sysTime.year))
                                    {
                                        sysTime.leapYear = 1;
                                    }
                                        
                                }
                                
                            }
                            
                          }
                          else if(sysTime.day == 32)
                          {
                            sysTime.month += 1;
                            sysTime.day = 0;
                            
                            if(sysTime.month == 13)
                            {
                                sysTime.month = 1;
                                if(isLeapYear(sysTime.year))
                                {
                                    sysTime.leapYear = 1;
                                }
                                        
                            }
                            
                          }
                    }
                }
            }
        }
    }
    else // SEC
    {
        
        sysTime.seconds += 1;
        init_PCB_LIGHT_toggle();
            
        if(sysTime.seconds == 60)
        {
            sysTime.minutes += 1;
            sysTime.seconds = 0;

            if(sysTime.minutes == 60)
            {
                sysTime.minutes = 0;
                 sysTime.hour += 1;

                if(sysTime.hour == 24)
                {

                    sysTime.hour = 0;
                    sysTime.day += 1;

                    // Determine month to process month rollover:
                    if(sysTime.day == 29)
                    {

                        if(sysTime.month == FEBRUARY)
                        {
                            if(!sysTime.leapYear))
                             {

                                sysTime.month += 1;
                                sysTime.day = 0;

                                if(sysTime.month == 13)
                                {
                                    sysTime.month = 1;
                                    if(isLeapYear(sysTime.year))
                                    {
                                        sysTime.leapYear = 1;
                                    }

                                }

                             }
                        }

                     }
                      else if(sysTime.day == 30)
                      {

                        if(sysTime.month == FEBRUARY)
                        {
                            sysTime.month += 1;
                            sysTime.day = 0;

                            if(sysTime.month == 13)
                            {
                                sysTime.month = 1;
                                if(isLeapYear(sysTime.year))
                                {
                                    sysTime.leapYear = 1;
                                }

                            }

                        }

                      }
                      else if(sysTime.day == 31)
                      {

                        if(is30dayMonth(sysTime.month))
                        {
                            sysTime.month += 1;
                            sysTime.day = 0;

                            if(sysTime.month == 13)
                            {
                                sysTime.month = 1;
                                if(isLeapYear(sysTime.year))
                                {
                                    sysTime.leapYear = 1;
                                }

                            }

                        }

                      }
                      else if(sysTime.day == 32)
                      {
                        sysTime.month += 1;
                        sysTime.day = 0;

                        if(sysTime.month == 13)
                        {
                            sysTime.month = 1;
                            if(isLeapYear(sysTime.year))
                            {
                                sysTime.leapYear = 1;
                            }

                        }

                      }
                }
            }
        }
    }
}
