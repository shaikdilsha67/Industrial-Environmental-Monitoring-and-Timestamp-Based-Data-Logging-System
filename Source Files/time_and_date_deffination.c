#include "types.h"        // Includes user-defined data types such as u8, u32, s8
#include "rtc.h"         // Includes RTC functions for reading and setting date and time
#include "lcd.h"         // Includes LCD display functions
#include "lcd_defines.h" // Includes LCD command and position macros
#include "delay.h"       // Includes delay functions
#include "display.h"     // Includes display-related function declarations

void set_temp_limit(void);                  // Function declaration to set the temperature limit
u32 is_valid_time(u32 h, u32 m, u32 s);  // Checks whether hour, minute and second values are valid
u32 is_valid(u32 d, u32 mon, u32 y);     // Checks whether the given date, month and year are valid

u32 d,mon,y,h,m,s;       // Global variables to store date and time values
u32 digit[4]={0},res;    // Stores keypad digits and the return value of get_input()

void set_hours(void)
{
    read_rtc_values(&h,&m,&s,&d,&mon,&y); // Reads the current RTC time and date into variables

        L:res=get_input("ENTER HOURS:",2,1,digit); // Displays the prompt and gets hour digits from the keypad

        if(res == 2)                              // Checks whether two digits were entered
    h = digit[0]*10 + digit[1];                  // Combines the two digits to form the hour
        else                                      // If only one digit was entered
        h =  digit[0]*1;                           // Stores the single digit as the hour

          if(h<=23)                                 // Checks whether the hour is within the valid range
                {
         set_rtc(&h,&m,&s,&d,&mon,&y);          // Updates RTC with the new hour and existing date/time values
                }
                else                                  // If the entered hour is invalid
                {
                        cmdLCD(CLEAR_LCD);            // Clears the LCD
                        strLCD("INVALID HOUR");        // Displays an invalid-hour message
                        goto L;                        // Goes back to the label L to enter the hour again
                }
}

void set_minutes(void)
{
          read_rtc_values(&h,&m,&s,&d,&mon,&y);    // Reads the current RTC values

        L:res=get_input("ENTER MINUTES:",2,1,digit); // Gets the minute value from the keypad

        if(res == 2)                                // Checks whether two digits were entered
    m = digit[0]*10 + digit[1];                     // Combines two digits to form minutes
        else                                          // If only one digit was entered
        m =  digit[0]*1;                               // Stores the single digit as minutes

          if(m<=59)                                    // Checks whether minutes are in the valid range
                {
     set_rtc(&h,&m,&s,&d,&mon,&y);               // Updates RTC with the new minute value
                }
                else                                      // If the minute value is invalid
                {
                        cmdLCD(CLEAR_LCD);                // Clears the LCD
                        strLCD("INVALID MINUTE");          // Displays an invalid-minute message
                        goto L;                            // Asks the user to enter minutes again
                }
}

void set_seconds(void)
{
          read_rtc_values(&h,&m,&s,&d,&mon,&y);       // Reads the current RTC values

        L:res=get_input("ENTER SECONDS:",2,1,digit);   // Gets the seconds value from the keypad

        if(res == 2)                                    // Checks whether two digits were entered
    s = digit[0]*10 + digit[1];                         // Combines two digits to form seconds
        else                                              // If only one digit was entered
        s =  digit[0]*1;                                   // Stores the single digit as seconds

          if(s<=59)                                        // Checks whether seconds are within the valid range
                {
           set_rtc(&h,&m,&s,&d,&mon,&y);              // Updates RTC with the new second value
                }
                else                                          // If the second value is invalid
                {
                        cmdLCD(CLEAR_LCD);                    // Clears the LCD
                        strLCD("INVALID SEC");                  // Displays an invalid-second message
                        goto L;                                // Asks the user to enter seconds again
                }
}

void set_date(void)
{
         read_rtc_values(&h,&m,&s,&d,&mon,&y);           // Reads the current RTC date and time

        L:res=get_input("ENTER DATE:",2,1,digit);         // Gets the day value from the keypad

    if(res == 2)                                           // Checks whether two digits were entered
    d = digit[0]*10 + digit[1];                            // Combines two digits to form the date
        else                                                 // If only one digit was entered
        d =  digit[0]*1;                                      // Stores the single digit as the day

        if(is_valid(d,mon,y))                                // Checks whether the entered date is valid
        {
         set_rtc(&h,&m,&s,&d,&mon,&y);                   // Updates RTC with the new date
        }
        else                                                  // If the date is invalid
        {
                  cmdLCD(CLEAR_LCD);                           // Clears the LCD
                  strLCD("INVALID DATE");                       // Displays an invalid-date message
                        goto L;                                 // Asks the user to enter the date again
        }
}

void set_month(void)
{
          read_rtc_values(&h,&m,&s,&d,&mon,&y);             // Reads the current RTC values

        L:res=get_input("ENTER MONTH:",2,1,digit);          // Gets the month value from the keypad

    if(res == 2)                                             // Checks whether two digits were entered
    mon = digit[0]*10 + digit[1];                            // Combines two digits to form the month
        else                                                   // If only one digit was entered
        mon =  digit[0]*1;                                      // Stores the single digit as the month

          if(is_valid(d,mon,y))                                 // Checks whether the date is valid for the entered month
                {
      set_rtc(&h,&m,&s,&d,&mon,&y);                         // Updates RTC with the new month
                }
                else                                             // If the month/date combination is invalid
                {
                        cmdLCD(CLEAR_LCD);                       // Clears the LCD
                        cmdLCD(GOTO_LINE1_POS0);                 // Moves the LCD cursor to the first line
                        strLCD("INVALID MONTH");                  // Displays an invalid-month message
                        goto L;                                   // Asks the user to enter the month again
                }
}

void set_year(void)
{
         read_rtc_values(&h,&m,&s,&d,&mon,&y);              // Reads the current RTC values

        L:res=get_input("ENTER YEAR:",4,2,digit);             // Gets the year input (up to four digits)

         if(res == 4)                                           // Checks whether four digits were entered
     y = digit[0]*1000 + digit[1]*100+ digit[2]*10 + digit[3]; // Combines four digits to form the year
         else                                                    // If fewer digits were entered
         y = digit[2]*10 + digit[3];                              // Forms a two-digit year from the last two digit positions

         if(is_valid(d,mon,y))                                    // Checks whether the date is valid for the entered year
         {
    set_rtc(&h,&m,&s,&d,&mon,&y);                              // Updates RTC with the new year
         }
         else                                                      // If the date/year combination is invalid
         {
                 cmdLCD(CLEAR_LCD);                                // Clears the LCD
                 strLCD("INVALID YEAR");                            // Displays an invalid-year message
                 goto L;                                            // Asks the user to enter the year again
         }
}


void set_rtc_input(void)
{
         read_rtc_values(&h,&m,&s,&d,&mon,&y);              // Reads the current date and time from RTC

     L:
         res=get_input("ENTER HOURS:", 2,1, digit);            // Gets hour input from keypad
         if(res ==2)                                            // Checks whether two digits were entered
     h = digit[0]*10 + digit[1];                                 // Combines two digits to form hours
         else                                                     // If one digit was entered
          h = digit[0]*1;                                          // Stores the single digit as hours

         res=get_input("ENTER MINUTES:", 2,1, digit);            // Gets minute input from keypad
         if(res==2)                                                // Checks whether two digits were entered
     m = digit[0]*10 + digit[1];                                   // Combines two digits to form minutes
         else                                                       // If one digit was entered
          m = digit[0]*1;                                            // Stores the single digit as minutes

         get_input("ENTER SECONDS:", 2,1, digit);                  // Gets seconds input from keypad
         if(res ==2)                                                 // Checks the value of res
     s = digit[0]*10 + digit[1];                                    // Combines two digits to form seconds
         else                                                         // If res is not 2
          s = digit[0]*1;                                              // Stores the first digit as seconds

                res=get_input("ENTER DATE:", 2,1, digit);             // Gets the day input
                if(res ==2)                                            // Checks whether two digits were entered
                d = digit[0]*10 + digit[1];                            // Combines two digits to form date
            else                                                       // If one digit was entered
                d = digit[0]*1;                                          // Stores the single digit as date

                res=get_input("ENTER MONTH:", 2,1, digit);              // Gets the month input
                if(res == 2)                                              // Checks whether two digits were entered
                mon = digit[0]*10 + digit[1];                            // Combines two digits to form month
                else                                                      // If one digit was entered
                 mon = digit[0]*1;                                        // Stores the single digit as month

                res=get_input("ENTER YEAR:", 4,2, digit);                // Gets year input (up to four digits)
                if(res==4)                                                  // Checks whether four digits were entered
                y = digit[0]*1000 + digit[1]*100+ digit[2]*10 + digit[3]; // Combines four digits to form year
                else                                                        // If fewer digits were entered
                y = digit[2]*10 + digit[3];                                  // Forms year from last two digits

                        if((is_valid(d,mon,y)) && (is_valid_time(h,m,s))) // Checks both date and time validity
                        {
             set_rtc(&h, &m, &s, &d, &mon, &y);                       // Updates RTC with the entered date and time
             cmdLCD(CLEAR_LCD);                                               // Clears the LCD
                        }
                        else                                                  // If either date or time is invalid
                        {
                          cmdLCD(CLEAR_LCD);                                   // Clears the LCD
                      strLCD("INVALID DATA");                                 // Displays an invalid-data message
                      goto L;                                                   // Repeats the entire date/time-entry process
                    }
}

u32 is_valid_time(u32 h, u32 m, u32 s)
{
    if(h <= 23 && m <= 59 && s <= 59) // Checks whether hour, minute and second are within valid ranges
    {
        return 1;                      // Returns 1 if the time is valid
    }
    else
    {
        return 0;                      // Returns 0 if the time is invalid
    }
}

u32 get_max_days(u32 mon, u32 y)
{
    if(mon == 2)                       // Checks whether the month is February
    {
        if((y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0))) // Checks the leap-year rule
                                {
            return 29;                  // Returns 29 days for leap-year February
                                }
        else
                                {
            return 28;                  // Returns 28 days for non-leap-year February
                                }
    }
    else if(mon == 4 || mon == 6 || mon == 9 || mon == 11) // Checks months having 30 days
                {
        return 30;                      // Returns 30 days
                }
    else if(mon >= 1 && mon <= 12)    // Checks whether month is between 1 and 12
                {
        return 31;                      // Returns 31 days for the remaining months
                }

    return 0;                            // Returns 0 if the month is invalid
}

u32 is_valid(u32 d, u32 mon, u32 y)
{
    u32 max_days;                        // Variable to store the maximum number of days in the given month

    if(mon < 1 || mon > 12 || y == 0)  // Checks whether month is invalid or year is zero
                {
        return 0;                        // Returns 0 when month or year is invalid
                }

    max_days = get_max_days(mon, y);    // Gets the maximum valid days for the given month and year

    if(d >= 1 && d <= max_days)        // Checks whether day is within the valid range
                {
        return 1;                        // Returns 1 if the date is valid
                }
    else
                {
        return 0;                        // Returns 0 if the date is invalid
                }
}

extern u8 temp_limit;                  // Declares temp_limit as a global variable defined in another source file

void set_temp_limit(void)
{
  u8 new_limit;                         // Local variable to store the new temperature limit

  L:                                    // Label used to repeat input when the temperature limit is invalid
    res=get_input("ENTER TEMP LIMIT:",2,1,digit); // Gets the temperature limit from the keypad

    if(res == 2)                          // Checks whether two digits were entered
    new_limit = digit[0]*10 + digit[1];  // Combines two digits to form the temperature limit
        else                                // If only one digit was entered
        new_limit =  digit[0]*1;            // Stores the single digit as the temperature limit

        if( new_limit > 15 && new_limit < 100) // Checks whether temperature limit is between 16 and 99
        {
         temp_limit = new_limit;             // Stores the valid limit in the global variable temp_limit
        }
        else                                 // If the temperature limit is invalid
        {
                  cmdLCD(CLEAR_LCD);          // Clears the LCD
                  strLCD("INVALID TEMP");      // Displays an invalid-temperature message
                  goto L;                      // Asks the user to enter the temperature limit again
        }
}
