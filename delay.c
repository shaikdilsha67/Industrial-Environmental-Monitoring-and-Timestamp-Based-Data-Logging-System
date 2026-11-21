#include "types.h"   // Include user-defined data types such as u32

// Function to generate delay in microseconds
void delay_us(u32 dlyus)
{
    // Multiply the requested microseconds by 12
    // to adjust the loop count according to the processor clock
    dlyus*=12;

    // Execute an empty loop until the counter reaches zero
    // Each iteration consumes processor time
    while(dlyus--);
}

// Function to generate delay in milliseconds
void delay_ms(u32 dlyms)
{
    // Multiply milliseconds by 12000 to calculate loop count
    dlyms*=12000;

    // Execute the loop repeatedly to generate delay
    while(dlyms--);
}

// Function to generate delay in seconds
void delay_s(u32 dlys)
{
    // Multiply seconds by 12000000 to calculate loop count
    dlys*=12000000;

    // Execute the loop repeatedly to generate delay
    while(dlys--);
}