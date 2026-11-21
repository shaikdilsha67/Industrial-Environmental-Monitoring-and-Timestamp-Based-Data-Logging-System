#include "types.h"  // Include user-defined data types such as u8 and f32

// Function declaration to read LM35 temperature in Celsius
// tdegc = pointer to store temperature in degree Celsius
void read_lm35(u8 *tdegc);

// Function declaration to read LM35 temperature in Celsius and Fahrenheit
// tdegc = pointer to store temperature in Celsius
// tdegf = pointer to store temperature in Fahrenheit
void read_lm35NP(f32 *tdegc,f32 *tdegf);
