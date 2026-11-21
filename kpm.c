#include<LPC21xx.h>        // Includes LPC2148 register definitions
#include "defines.h"        // Includes user-defined macros
#include "kpm_defines.h"  // Includes keypad pin definitions and macros
#include "lcd.h"           // Includes LCD function declarations
#include "lcd_defines.h"   // Includes LCD command and pin definitions


// Lookup table (LUT) to convert row and column positions into key values
int kpmlut[4][4]=
{
    {1,2,3,'A'},          // Row 0: returns 1, 2, 3, A
    {4,5,6,'B'},          // Row 1: returns 4, 5, 6, B
    {7,8,9,'C'},          // Row 2: returns 7, 8, 9, C
    {'*',0,'#','D'}      // Row 3: returns *, 0, #, D
};


// Function to check whether any key is pressed
unsigned int colscan(void)
{
    unsigned int status;                    // Variable to store column pin status

    status=READNIBBLE(IOPIN1,COL0);        // Read all 4 column pins starting from COL0

    return ((status<15)?0:1);                // If any column is LOW, return 0 (key pressed)
                                             // If all columns are HIGH, return 1 (no key pressed)
}


// Function to identify which row contains the pressed key
unsigned int rowcheck(void)
{
    unsigned int r;                          // Variable to count row numbers (0 to 3)

    for(r=0;r<=3;r++)                       // Check each row one by one
    {
        WRITENIBBLE(IOPIN1,ROW0,~(1<<r));   // Make the selected row LOW and other rows HIGH

        if((colscan())==0)                    // Check whether any column becomes LOW
        {
            break;                              // If a key is detected, stop row scanning
        }
    }

    WRITENIBBLE(IOPIN1,ROW0,0);              // Clear/reset the row output nibble
    return r;                                  // Return the detected row number
}


// Function to identify which column contains the pressed key
unsigned int colcheck(void)
{
    unsigned int c;                             // Variable to count column numbers (0 to 3)

    for(c=0;c<=3;c++)                           // Check columns one by one
    {
        if(READBIT(IOPIN1,COL0+c)==0)            // Check if the current column pin is LOW
        {
            break;                                 // If LOW, the key is in this column; stop
        }
    }

    return c;                                      // Return the detected column number
}


// Function to scan the keypad and identify which key was pressed
unsigned int keyscan(void)
{
    unsigned int row,col,keyv;                     // Variables for row, column, and key value

    while(colscan());                               // Wait until a key is pressed
                                                    // colscan() returns 1 when no key is pressed

    row=rowcheck();                                  // Find the row of the pressed key
    col=colcheck();                                  // Find the column of the pressed key

    keyv=kpmlut[row][col];                          // Get key value using row and column from LUT

    return keyv;                                      // Return the actual key value
}


// Function to configure keypad GPIO pins
void initkpm(void)
{
    // All rows configured as outputs

    IODIR1|=0xF<<ROW0;                               // Set 4 row pins as output pins

    // All columns configured as inputs

    IODIR1&=~(0xF<<COL0);                              // Set 4 column pins as input pins
}
