#include <LPC21xx.h>                 // Includes LPC2148 register definitions
#include "types.h"                   // Includes user-defined data types like u8 and u32
#include "rtc.h"                     // Includes RTC variables such as HOUR, MIN, SEC, DOM, MONTH, YEAR
#include "uart.h"                    // Includes UART function declarations

void send_temp(u8 t)                  // Function to transmit temperature through UART
{                                     
    u0_txu32(t);                      // Sends the temperature value as decimal digits
    uart_tx(0xB0);                    // Transmits 0xB0 (degree symbol code)
    uart_tx('C');                      // Transmits character C to represent Celsius
}                                     


void send2(u32 n)                      // Function to transmit a number in two-digit format
{                                      
    uart_tx((n / 10) + '0');           // Extracts tens digit and converts it to ASCII
    uart_tx((n % 10) + '0');          // Extracts ones digit and converts it to ASCII
}                                      

void send_log(u8 tempc)                 // Function to send date, time, and temperature log through UART
{                                       
    u0_txstr("\r\n");                   // Sends carriage return and newline
    u0_txstr("REAL-TIME SENSOR DATA\r\n"); // Sends the sensor data heading
    u0_txstr("*************************************************************\r\n"); // Sends separator line
    u0_txstr("DATA    TIME    TEMPERATURE\r\n"); // Sends column headings
    u0_txstr("*************************************************************\r\n"); // Sends separator line

    /* Send date: DD/MM/YYYY */
    send2(DOM);                          // Sends the day in two-digit format
    uart_tx('/');                        // Sends date separator /
    send2(MONTH);                        // Sends the month in two-digit format
    uart_tx('/');                        // Sends date separator /
    u0_txu32(YEAR);                       // Sends the year as decimal digits

    u0_txstr("    ");                     // Sends spaces between date and time

    /* Send time: HH:MM:SS */
    send2(HOUR);                          // Sends hours in two-digit format
    uart_tx(':');                         // Sends time separator :
    send2(MIN);                            // Sends minutes in two-digit format
    uart_tx(':');                         // Sends time separator :
    send2(SEC);                             // Sends seconds in two-digit format

    u0_txstr("    ");                     // Sends spaces between time and temperature

    /* Send temperature */
    u0_txu32(tempc);                      // Sends temperature value as decimal digits
    uart_tx(223);                           // Sends character code 223 (intended degree symbol)
    uart_tx('C');                            // Sends C to indicate Celsius

    /* Next line */
    uart_tx('\r');                           // Sends carriage return
    uart_tx('\n');                            // Sends newline
}


void send_alert(u8 tempc)                  // Function to transmit temperature alert message
{                                          
 u0_txstr("Alert Temperature:");           // Sends alert message through UART
 u0_txu32(tempc);                         // Sends the current temperature value
 uart_tx('C');                             // Sends C to indicate Celsius
 uart_tx('\r');                            // Sends carriage return
 uart_tx('\n');                            // Sends newline
}                                          

void time(void)                             // Function to transmit current RTC time through UART
{                                           
    /* Send time: HH:MM:SS */
    send2(HOUR);                             // Sends hours as two digits
    uart_tx(':');                             // Sends colon separator
    send2(MIN);                               // Sends minutes as two digits
    uart_tx(':');                             // Sends colon separator
    send2(SEC);                                // Sends seconds as two digits
}                     
