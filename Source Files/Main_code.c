#include <LPC21xx.h>       // Includes LPC2148 hardware register definitions
#include "types.h"         // Includes user-defined data types
#include "delay.h"        // Includes delay functions
#include "rtc.h"          // Includes RTC functions for time and date
#include "lcd.h"          // Includes LCD display functions
#include "lcd_defines.h" // Includes LCD commands and cursor positions
#include "interrupt.h"    // Includes external interrupt functions and flags
#include "kpm.h"         // Includes keypad functions
#include "adc.h"         // Includes ADC initialization and reading functions
#include "lm35.h"       // Includes LM35 temperature sensor functions
#include "display.h"     // Includes LCD data display function
#include "uart.h"       // Includes UART communication functions
#include "data_log.h"   // Includes temperature logging and alert functions
#include "menu.h"       // Includes menu functions for setting RTC and temperature limit

u32 temp_limit=40,r;    // temp_limit stores the temperature threshold (40°C initially); r stores the menu return value

#define LOG_INTERVAL_MIN 1 // Defines the temperature logging interval in minutes

int main()
{

        //variable to store previously read rtc values
        u32 last_min,last_hr,last_day; // Stores previous minute, hour and day values to detect RTC changes
        u32 min = 0;                   // Counter used to track the logging interval
        //variable to store temp in celsius
        u8 tempc;                       // Stores the temperature value in Celsius
        //Initialize the lcd
    initLCD();                           // Initializes the LCD display
        //Initialize the kpm
        initkpm();                        // Initializes the keypad
        //Initialize the adc to read lm35 sensor data
        init_adc();                        // Initializes the ADC peripheral
        //Initialize External Interrupt 0
    initEINT0();                          // Configures External Interrupt 0 for RTC setting menu
    //Initialize uart communication
        uart_init();                        // Initializes UART communication
    //Initialize the real time clock
    initRTC();                             // Initializes the RTC peripheral
        //store the current rtc minute
        last_min = MIN;                      // Stores the current RTC minute
        //store the current rtc hour
    last_hr = HOUR;                         // Stores the current RTC hour
        //store the current date
    last_day = DOM;                          // Stores the current day of the month

        //p0.23 set as I/O direction
        IODIR0|= (1<<23);                   // Configures P0.23 as an output pin
        //Initially clear p0.23
        IOCLR0=1<<23;                         // Initially turns OFF the buzzer connected to P0.23

    u0_txstr("=============================================================\r\n"); // Prints a separator line on the terminal
    u0_txstr("INDUSTRIAL ENVIRONMENT MONITORING SYSTEM\r\n");                 // Prints the project title
        u0_txstr("ARM LPC2148|REAL-TIME DATA LOGGER\r\n");                        // Prints the controller and project description
        u0_txstr("=============================================================\r\n"); // Prints a separator line
    u0_txstr("SYSTEM CONFIGURATION\r\n");                                           // Prints the configuration heading
        u0_txstr("=============================================================\r\n"); // Prints a separator line
        u0_txstr("Temperature Limit :");                                            // Prints the temperature limit label
        send_temp(temp_limit);                                                        // Sends/displays the current temperature limit
        u0_txstr("\r\n");                                                             // Moves to the next line
        u0_txstr("Monitoring Status :Active\r\n");                                    // Prints monitoring status
    u0_txstr("RTC Status        :RUNNING\r\n");                                      // Prints RTC status
        u0_txstr("=============================================================\r\n"); // Prints a separator line
    send_log(tempc);                                                                 // Sends the initial temperature log

            while(1)                                                                  // Starts an infinite loop for continuous monitoring
        {

                  //read temp from lm35 using adc
                  //store celsius value in tempc
          read_lm35(&tempc);                                                          // Reads LM35 temperature through ADC and stores it in tempc

                  //check whether the temperature exceeds the predefined limit
                  if(tempc > temp_limit)                                               // Checks whether temperature is greater than the set limit
                  {
                   //turn  on the buzzer
                   IOSET0 = (1<<23);                                                     // Turns ON the buzzer using P0.23
                   u0_txstr("TEMPERATURE ALERT\r\n");                                    // Prints temperature alert message
                   u0_txstr("------------------------------------------------------------\r\n"); // Prints separator line
                   send_alert(tempc);                                                     // Sends the current high temperature alert value
                   u0_txstr("Buzzer Status :ACTIVATED\r\n");                             // Prints buzzer activation status
                   u0_txstr("------------------------------------------------------------\r\n"); // Prints separator line
                   //buzzer ON 500ms
                   delay_ms(500);                                                          // Keeps the buzzer ON for 500 milliseconds
                   //after 500ms buzzer will be OFF
                   IOCLR0 = (1<<23);                                                        // Turns OFF the buzzer using P0.23
                  }
                   //check wether the external interrupt requt rtc time setting
           if(set_time_flag ==1)                                                            // Checks whether the external interrupt flag is set
           {
                     //reset the flag to prevent repeated execution
             set_time_flag=0;                                                                // Clears the flag so this event is not processed repeatedly

                         u0_txstr("SYSTEM EVENT LOG\r\n");                                   // Prints the system event log heading
                         u0_txstr("------------------------------------------------------------\r\n"); // Prints separator line
                         u0_txstr("Interrupt Raised\r\n");                                     // Prints that an interrupt occurred
                         time();                                                               // Sends the current RTC time through UART
                         r=Menu_top();                                                         // Opens the main menu and stores the selected key
                         if(r == 1)                                                            // Checks whether temperature limit option was selected
                         {
                          u0_txstr(" | ");                                                     // Prints a separator
                          u0_txstr("Setpoint Updated\r\n");                                   // Prints that the temperature setpoint was updated
                          time();                                                               // Sends the current time through UART
                          u0_txstr(" | ");                                                     // Prints a separator
                          u0_txstr("Updated Setpoint is :");                                  // Prints the updated setpoint label
                  send_temp(temp_limit);                                                        // Sends the newly updated temperature limit
                         }
                         else                                                                 // If option 1 was not selected
                         {
                         u0_txstr("\r\n");                                                     // Prints a new line
                         u0_txstr("RTC Updated\r\n");                                          // Prints RTC update status
                         time();                                                               // Sends the current RTC time through UART
                         }
           }

                  //display the current temp,time and date on lcd
                  display_data(tempc);                                                         // Displays temperature, date and time on the LCD

          //check whethter the minute,hour or date has changed

          if (MIN != last_min || HOUR != last_hr || DOM != last_day)                          // Checks whether minute, hour or date changed
              {
                   //increment the minute cnt when rtc time/date changes
               min++;                                                                         // Increments the logging counter when a time/date change is detected
                   //check whether the required logging interval is reached
           if(min >= LOG_INTERVAL_MIN)                                                         // Checks whether the logging interval has been reached
               {
                    //send the current temperature data through uart
                send_log(tempc);                                                               // Sends current date, time and temperature through UART
                        //reset the minute cnt after sending the log
                min = 0;                                                                        // Resets the logging counter after sending the log
                }
           }

                  //store the current rtc minute for the next comparison
              last_min = MIN;                                                                    // Updates the previous minute value
                  //store the current rtc hour for next comparison
              last_hr = HOUR;                                                                    // Updates the previous hour value
                  //store the current rtc date for the next comparison
              last_day = DOM;                                                                     // Updates the previous day value

        }

}
