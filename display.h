#include "types.h"              // Includes user-defined data types such as u8, u32, and s8

void display_data(u8 tempc);    // Function declaration: displays date, time, and temperature on the LCD

u32 get_input(s8 *str, u32 c1, u32 c2, u32 *digit); // Function declaration: gets input from the user through the keypad and returns the input value
