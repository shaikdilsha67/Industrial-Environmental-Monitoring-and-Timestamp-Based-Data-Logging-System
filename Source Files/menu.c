#include "lcd_defines.h" // Includes LCD command and cursor-position definitions
#include "lcd.h"         // Includes LCD functions such as cmdLCD() and strLCD()
#include "kpm.h"        // Includes keypad functions such as keyscan() and colscan()
#include "delay.h"      // Includes delay functions
#include "types.h"      // Includes user-defined data types such as u32
#include "rtc.h"       // Includes RTC functions for date and time handling
#include "Menu.h"      // Includes menu-related function declarations

u32 key;               // Global variable to store the key pressed by the user

u32 Menu_top(void)     // Function to display and handle the main menu
{
  cmdLCD(CLEAR_LCD);            // Clears the LCD display
  cmdLCD(GOTO_LINE1_POS0);      // Moves the cursor to the beginning of line 1
  strLCD("1.SET TEMP LIMIT");    // Displays option 1: Set temperature limit
  cmdLCD(GOTO_LINE2_POS0);      // Moves the cursor to the beginning of line 2
  strLCD("2.SET RTC");           // Displays option 2: Set RTC date and time
  cmdLCD(GOTO_LINE3_POS0);      // Moves the cursor to the beginning of line 3
  strLCD("3.EXIT");              // Displays option 3: Exit

        key=keyscan();           // Scans the keypad and stores the pressed key in key
        delay_ms(500);          // Adds a 500 ms delay to avoid immediate repeated input
        while(!colscan());     // Waits until the pressed key is released

        if(key == 1)           // Checks whether the user selected option 1
        {
     set_temp_limit();        // Calls the function to set the temperature limit
        }
        else if(key == 2)      // Checks whether the user selected option 2
        {
         Menu();               // Calls the RTC submenu to set time/date
        }
        else                   // If any other key is pressed (including option 3)
        {
                return;         // Exits the function without returning a specific value
        }

        return key;             // Returns the pressed key value
}

void Menu(void)                // Function to display and handle the RTC submenu
{
  cmdLCD(CLEAR_LCD);            // Clears the LCD display
  cmdLCD(GOTO_LINE1_POS0);      // Moves the cursor to the beginning of line 1
  strLCD("1.SET TIME");         // Displays option 1: Set time
  cmdLCD(GOTO_LINE2_POS0);      // Moves the cursor to the beginning of line 2
  strLCD("2.SET DATE");         // Displays option 2: Set date
  cmdLCD(GOTO_LINE3_POS0);      // Moves the cursor to the beginning of line 3
  strLCD("3.SET BOTH");         // Displays option 3: Set both date and time
  cmdLCD(GOTO_LINE4_POS0);      // Moves the cursor to the beginning of line 4
  strLCD("4.EXIT");             // Displays option 4: Exit submenu

        key=keyscan();           // Scans the keypad and stores the pressed key
        delay_ms(500);          // Adds a 500 ms delay
        while(!colscan());     // Waits until the user releases the pressed key

        if(key == 1)           // Checks whether option 1 (Set Time) is selected
        {
     time_menu();              // Calls the time-setting menu
        }
        else if(key == 2)       // Checks whether option 2 (Set Date) is selected
        {
           date_menu();          // Calls the date-setting menu
        }
        else if(key == 3)       // Checks whether option 3 (Set Both) is selected
        {
                set_rtc_input(); // Calls the function to set both date and time
        }
        else                    // If option 4 or another key is pressed
        {
                Menu_top();       // Returns to the main menu
        }

}
