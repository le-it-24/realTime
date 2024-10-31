/* 
 * File:   systemTime.h
 * Author: Leonard
 *
 * Created on October 13, 2024, 8:39 AM
 */




/***REALTIME & CALENDAR APP DEPENDENCIES***/
#include "realTime_config.h"
#include "pcbLight.h"
#include<stdio.h> 
#include "string.h"




/***PCB_LIGHT CONTROL METHODS***/
void init_PCB_LIGHT_toggle()
{
    enable_PCB_LIGHT();
    TOGGLE_PCB_LIGHT_FLAG = 1;
}




/***SYSTEM TIME STRUCTURE***/
struct time
{
    uint16_t microseconds;
    uint16_t milliseconds;
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;
    int leapYear;
};



/***STRING PROCESSING METHODS FOR SYSTEM TIME OUTPUT***/

// Method for returning first occurence of specified character found after specified index:
int getFirstOccurenceOfChar(char* string, char character, uint8_t index)
{
  // Start searching for character from first index:
  for (uint8_t i = index; i < strlen(string); i++)
    {
      // If character is found, return index:
      if (string[i] == character)
      {
        return i;
      }
      
    }

  // If character is not found, return -1:
  return -1;
}

// Method inserts a substring between two specified points in a target string:
void pasteIntoString(int start, int end, char *string, char *substring)
{
    // Configure temp tempString
    int targetSize = strlen(string);
    int substringSize = strlen(substring);
  int totalSize = targetSize + substringSize;
    char *tempString = (char *)malloc((totalSize+1) * sizeof(char));

    // Add characters before start to temp string:
    for(int c = 0; c < start; c++)
    {
        tempString[c] = string[c];
    }

    // Insert substring to temp string:
    int index = start;
    for(int c = 0; c < substringSize; c++)
    {
      tempString[index] = substring[c];
      index+=1;
    }

    // Insert remaining string content to temp-string:
    int appendAt = start + substringSize;
    for(int c = end+1; c < targetSize; c++)
    {
        tempString[appendAt] = string[c];
          appendAt+=1;
    }
    // Add null terminator to temp string:
  tempString[totalSize] = '\0';
  printf("%s\n", tempString);
    // Transfer assembled string data:
    strcpy(string, tempString);

    // Free temp string:
    free(tempString);
  
}




/***SYSTEM TIMING VARIABLES***/
struct time sysTime;
int SYSTIME_SYNC_REQUIRED; // Flag raised when it's time to sync system time over internet.
char timeNow[40];




/***REALTIME DATA ACQUISTION METHODS***/
void setCstring_realTime()
{
    
    char year[5];
    sprintf(year,"%"PRIu16,sysTime.year);
    char month[3];
    sprintf(month,"%"PRIu8,sysTime.month);
    char day[3];
    sprintf(day,"%"PRIu8,sysTime.day);
    char hour[3];
    sprintf(hour,"%"PRIu8,sysTime.hour);
    char min[3];
    sprintf(min,"%"PRIu8,sysTime.minutes);
    char s[3];
    sprintf(s,"%"PRIu8,sysTime.seconds);
    char ms[5];
    sprintf(ms,"%"PRIu16,sysTime.milliseconds);
    char us[5];
    sprintf(us,"%"PRIu16,sysTime.microseconds);
    
    /***ASSEMBLE STRING***/
    int insertEndY = getFirstOccurenceOfChar(timeNow, '-', 0)-1;
    pasteIntoString(0, insertEndY, timeNow, year);
    
    // Insert month:
    strcat(timeNow,year);
    strcat(timeNow, "Y:");
    strcat(timeNow, month);
    strcat(timeNow, "M:");
    strcat(timeNow, hour);
    strcat(timeNow, "H:");
    strcat(timeNow, min);
    strcat(timeNow, "m:");
    strcat(timeNow, s);
    strcat(timeNow, "S:");
    strcat(timeNow, ms);
    strcat(timeNow, "ms:");
    strcat(timeNow, us);
    strcat(timeNow, "us:");
    
}

/***REALTIME DATA PROCESSING METHODS***/
int isLeapYear(uint16_t year) // Returns 1 if year is a leap.
{
    if(((year % 4 == 0) && (year%100 != 0))||(year%400 == 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int is30dayMonth(uint8_t month) // Returns 1 if month only has 30-days.
{
    for(int m = 0; m < 4; m++)
    {
        if(month == month_30DaysOnly[m])
        {
            return 1;
        }
    }
    
    return 0;
}



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
                                if(!sysTime.leapYear)
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
                            if(!sysTime.leapYear)
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
