#include <LPC21xx.h>       // Include LPC2148 register definitions
#include <stdlib.h>        // Include standard library functions
#include "rtc_defines.h"  // Include RTC clock and configuration macros
#include "types.h"        // Include user-defined data types (u32, etc.)
#include "lcd_defines.h" // Include LCD command macros
#include "lcd.h"         // Include LCD function declarations
#include "display.h"     // Include display-related functions
#include "kpm.h"        // Include keypad functions
#include "Menu.h"       // Include menu function declarations


// Initialize RTC
void initRTC(void)
{
    // Stop the RTC counter
    CCR = 0x00;

    // Reset RTC clock divider
    CCR = 0x02;

    // Clear the RTC clock divider reset
    CCR = 0x00;

    // Configure RTC prescaler for PCLK = 15 MHz
    // PREINT determines the integer portion of the RTC prescaler
    PREINT = (PCLK / 32768) - 1;

    // PREFRAC determines the fractional portion of the RTC prescaler
    PREFRAC = PCLK - ((PREINT + 1) * 32768);


    // Start RTC and enable the required clock control bit
    CCR = 0x01|1<<4;
}


// Function to set time and date in RTC registers
// h   = pointer to hours
// m   = pointer to minutes
// s   = pointer to seconds
// d   = pointer to day
// mon = pointer to month
// y   = pointer to year

void set_rtc(u32 *h,u32 *m,u32 *s,u32 *d,u32 *mon,u32 *y)
{
    // Set seconds register
    SEC=*s;

    // Set minutes register
    MIN=*m;

    // Set hours register
    HOUR=*h;

    // Set day of month register
    DOM=*d;

    // Set month register
    MONTH=*mon;

    // Set year register
    YEAR=*y;
}


// Function to read time and date from RTC registers
// Store the read values in the variables whose addresses are passed

void read_rtc_values(u32 *h,u32 *m,u32 *s,u32 *d,u32 *mon,u32 *y)
{
    // Read hours from RTC and store in the variable pointed to by h
    *h = HOUR;

    // Read minutes from RTC and store in the variable pointed to by m
    *m = MIN;

    // Read seconds from RTC and store in the variable pointed to by s
    *s = SEC;

    // Read day of month and store it in d
    *d = DOM;

    // Read month and store it in mon
    *mon = MONTH;

    // Read year and store it in y
    *y = YEAR;
}


// Function to receive keypad input and store entered digits
// msg = message to display on LCD
// c1  = first acceptable digit count
// c2  = second acceptable digit count
// digit = array to store the entered digits
u32 get_input(char *msg, u32 c1,u32 c2, u32 *digit)
{
    // i tracks the number of digits entered
    // key stores the key pressed on keypad
    u32 i = 0, key;


    // Move LCD cursor to the beginning of line 2
    cmdLCD(GOTO_LINE2_POS0);

    // Continuously scan keypad until valid completion condition occurs
    while(1)
    {
        // Read the pressed key from the keypad
        key = keyscan();

        // Wait 500 milliseconds to avoid rapid repeated input
        delay_ms(500);

        // Wait until keypad key is released
        while(!colscan());

        // Check whether this is the first key input
        if(i==0)
        {
            // Clear LCD before displaying the input message
            cmdLCD(CLEAR_LCD);

            // Move cursor to the beginning of line 1
            cmdLCD(GOTO_LINE1_POS0);

            // Display the message passed to the function
            strLCD(msg);

            // Move cursor to the beginning of line 2
            cmdLCD(GOTO_LINE2_POS0);
        }

        // Check whether the pressed key is a number from 0 to 9
        if(key <= 9)
        {
            // Store the pressed digit in the digit array
            digit[i] = key;

            // Display the entered digit on LCD
            u32LCD(digit[i]);

            // Increment index to store the next digit
            i++;
        }

        // Check whether '*' is pressed and at least one digit exists
        if((key == '*')&&(i>0))
        {
            // Shift the LCD display to the left
            cmdLCD(SHIFT_DISP_LEFT);

            // Display a blank space to erase the previous digit visually
            charLCD(' ');

            // Shift the LCD display to the left again
            cmdLCD(SHIFT_DISP_LEFT);

            // Decrement index to remove the last entered digit
            i--;
        }

        // Check whether '#' is pressed and digit count matches c1 or c2
        if((key =='#')&&(i==c1)||(key == '#')&&(i==c2))
        {
            // Clear the LCD display
            cmdLCD(CLEAR_LCD);

            // Move cursor to the beginning of line 1
            cmdLCD(GOTO_LINE1_POS0);

            // Display update confirmation message
            strLCD("Updated!!");

            // Return the number of digits entered
            return i;
        }
    }
}


// Function to display the time-setting menu
void time_menu(void)
{
    // Variable to store the selected keypad option
    u32 key;

    // Clear LCD display
    cmdLCD(CLEAR_LCD);

    // Move cursor to the beginning of line 1
    cmdLCD(GOTO_LINE1_POS0);

    // Display option 1: Set hours
    strLCD("1.SET HOURS");

    // Move cursor to the beginning of line 2
    cmdLCD(GOTO_LINE2_POS0);

    // Display option 2: Set minutes
    strLCD("2.SET MINUTES");

    // Move cursor to the beginning of line 3
    cmdLCD(GOTO_LINE3_POS0);

    // Display option 3: Set seconds
    strLCD("3.SET SECONDS");

    // Move cursor to the beginning of line 4
    cmdLCD(GOTO_LINE4_POS0);

    // Display option 4: Go back
    strLCD("4.BACK");

    // Read the selected key from the keypad
    key=keyscan();

    // Wait 500 milliseconds
    delay_ms(500);

    // Wait until the key is released
    while(!colscan());

    // If option 1 is selected, call the hours-setting function
    if(key == 1)
    {
        set_hours();
    }

    // If option 2 is selected, call the minutes-setting function
    else if(key == 2)
    {
        set_minutes();
    }

    // If option 3 is selected, call the seconds-setting function
    else if(key == 3)
    {
        set_seconds();
    }

    // If another key is selected, return to the main menu
    else
    {
        Menu();
    }
}


// Function to display the date-setting menu
void date_menu(void)
{
    // Variable to store the selected keypad option
    u32 key;

    // Clear LCD display
    cmdLCD(CLEAR_LCD);

    // Move cursor to the beginning of line 1
    cmdLCD(GOTO_LINE1_POS0);

    // Display option 1: Set date
    strLCD("1.SET DATE");

    // Move cursor to the beginning of line 2
    cmdLCD(GOTO_LINE2_POS0);

    // Display option 2: Set month
    strLCD("2.SET MONTH");

    // Move cursor to the beginning of line 3
    cmdLCD(GOTO_LINE3_POS0);

    // Display option 3: Set year
    strLCD("3.SET YEAR");

    // Move cursor to the beginning of line 4
    cmdLCD(GOTO_LINE4_POS0);

    // Display option 4: Go back
    strLCD("4.BACK");

    // Read the selected key from the keypad
    key=keyscan();

    // Wait 500 milliseconds
    delay_ms(500);

    // Wait until the key is released
    while(!colscan());

    // If option 1 is selected, call the date-setting function
    if(key == 1)
    {
        set_date();
    }

    // If option 2 is selected, call the month-setting function
    else if(key == 2)
    {
        set_month();
    }

    // If option 3 is selected, call the year-setting function
    else if(key == 3)
    {
        set_year();
    }

    // If another key is selected, return to the main menu
    else
    {
        Menu();
    }
}
