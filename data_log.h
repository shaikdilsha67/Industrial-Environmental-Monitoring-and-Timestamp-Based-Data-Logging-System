#include "types.h"  // Includes user-defined data types such as u32, u8, and s8

void send2(u32 n);
// Function prototype for send2().
// Accepts an unsigned 32-bit integer as an argument.
// Used to transmit a number in two-digit format through UART.

void send_log(u8 tempc);
// Function prototype for send_log().
// Accepts temperature in Celsius.
// Used to transmit date, time, and temperature sensor data through UART.

void send_alert(u8 tempc);
// Function prototype for send_alert().
// Accepts temperature as an argument.
// Used to transmit a temperature alert message through UART.

u32 get_input(s8 *str,u32 c1,u32 c2,u32 *digit);
// Function prototype for get_input().
// str: Pointer to a string containing the message to display.
// c1: First acceptable number of digits for input confirmation.
// c2: Second acceptable number of digits for input confirmation.
// digit: Pointer to an array used to store the entered digits.
// Returns the number of digits entered (u32).

void time(void);
// Function prototype for time().
// Used to transmit the current RTC time in HH:MM:SS format through UART.

void send_temp(u8 t);
// Function prototype for send_temp().
// Accepts temperature value t.
// Used to transmit temperature along with degree symbol and Celsius unit.