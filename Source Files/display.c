#include <LPC21xx.h>       // Includes LPC2148 register definitions
#include "types.h"         // Includes user-defined data types such as u8 and u32
#include "lcd.h"          // Includes LCD function declarations
#include "rtc.h"          // Includes RTC registers and date/time declarations
#include "display.h"      // Includes display-related function declarations
#include "lcd_defines.h" // Includes LCD command and position definitions
#include "kpm.h"         // Includes keypad function declarations

// Function to display date, time, and temperature on the LCD
void display_data(u8 tempc)
{
    // Row 1: Project title
    cmdLCD(GOTO_LINE1_POS0);       // Moves LCD cursor to the beginning of row 1
    strLCD("ENVIRONMENT MONITOR"); // Displays the project title on row 1

    // Row 2: Date
    cmdLCD(GOTO_LINE2_POS0);       // Moves LCD cursor to the beginning of row 2
    strLCD("Date: ");              // Displays the Date label

    if(DOM < 10)                   // Checks whether the day is a single-digit number
    charLCD('0');                  // Displays leading zero if day is less than 10
    u32LCD(DOM);                   // Displays the current day from the RTC

    charLCD('/');                  // Displays / as a date separator

    if(MONTH < 10)                 // Checks whether the month is a single-digit number
    charLCD('0');                  // Displays leading zero if month is less than 10
    u32LCD(MONTH);                // Displays the current month from the RTC

    charLCD('/');                  // Displays / as a date separator

    u32LCD(YEAR);                 // Displays the current year from the RTC
    strLCD("    ");              // Displays spaces after the date

    // Row 3: Time with seconds
    cmdLCD(GOTO_LINE3_POS0);      // Moves LCD cursor to the beginning of row 3
    strLCD("Time: ");             // Displays the Time label

    if(HOUR < 10)                  // Checks whether the hour is a single-digit number
    charLCD('0');                 // Displays leading zero if hour is less than 10
    u32LCD(HOUR);                // Displays the current hour from the RTC

    charLCD(':');                 // Displays colon as a time separator

    if(MIN < 10)                  // Checks whether the minute is a single-digit number
    charLCD('0');                // Displays leading zero if minute is less than 10
    u32LCD(MIN);                 // Displays the current minute from the RTC

    charLCD(':');                // Displays colon as a time separator

    if(SEC < 10)                 // Checks whether the second is a single-digit number
    charLCD('0');               // Displays leading zero if second is less than 10
    u32LCD(SEC);                // Displays the current second from the RTC

    strLCD("     ");           // Displays spaces after the time

    // Row 4: Temperature
    cmdLCD(GOTO_LINE4_POS0);    // Moves LCD cursor to the beginning of row 4
    strLCD("Temp: ");           // Displays the Temp label

    if(tempc < 10)              // Checks whether temperature is a single-digit number
    charLCD('0');              // Displays leading zero if temperature is less than 10
    u32LCD(tempc);            // Displays the temperature value

    //Temperature Symbol
    charLCD(0xDF);             // Displays the degree symbol (custom LCD character code)
    charLCD('C');              // Displays C to indicate Celsius
    strLCD("             ");   // Displays spaces to clear leftover characters on the LCD
}
