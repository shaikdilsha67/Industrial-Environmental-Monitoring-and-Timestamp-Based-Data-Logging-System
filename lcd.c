#include<LPC21xx.h>
#include "lcd_defines.h"   // Include LCD command and pin definitions
#include "defines.h"       // Include user-defined macros and pin definitions
#include "delay.h"        // Include delay function declarations

// Function to send a byte (command or data) to the LCD
void writeLCD(unsigned char byte)
{
  // Set RW = 0, which means write mode
  IOCLR0=1<<LCD_RW;

  // Place 8-bit data on the LCD data pins
  WRITEBYTE(IOPIN0,LCD_DATA,byte);

  // Make Enable pin HIGH to trigger LCD
  IOSET0=1<<LCD_EN;

  // Wait for 1 microsecond
  delay_us(1);

  // Make Enable pin LOW to complete the write operation
  IOCLR0=1<<LCD_EN;

  // Wait for LCD to process the command/data
  delay_ms(2);
}

// Function to send a command to the LCD
void cmdLCD(unsigned char cmd)
{
 // Set RS = 0 to select command register
 IOCLR0=1<<LCD_RS;

 // Send the command byte to the LCD
 writeLCD(cmd);

}

// Function to initialize the LCD
void initLCD(void)
{
 // Configure LCD data pins and RS, RW, EN pins as output
 IODIR0|=(0xFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN);

 // Wait 15 milliseconds after power ON
 delay_ms(15);

 // Send LCD initialization command 0x30
 cmdLCD(0x30);

 // Wait 4 milliseconds
 delay_ms(4);

 // Wait 100 microseconds
 delay_us(100);

 // Send LCD initialization command 0x30 again
 cmdLCD(0x30);

 // Wait 100 microseconds
 delay_us(100);

 // Send LCD initialization command 0x30 for the third time
 cmdLCD(0x30);

 // Configure LCD for 8-bit mode and 2 lines
 cmdLCD(MODE_8BIT_2LINE);

 // Turn ON display and turn OFF cursor
 cmdLCD(DSP_ON_CUR_OFF);

 // Clear all characters from the LCD
 cmdLCD(CLEAR_LCD);

 // Shift cursor position to the right after each character
 cmdLCD(SHIFT_CUR_RIGHT);
}

// Function to display a single character on the LCD
void charLCD(unsigned char asciival)
{
 // Set RS = 1 to select data register
 IOSET0=1<<LCD_RS;

 // Send the ASCII character to the LCD
 writeLCD(asciival);
}

// Function to display a string on the LCD
void strLCD(unsigned char *s)
{
 // Continue until the null character '\0' is reached
 while(*s)

 // Display the current character and move pointer to next character
 charLCD(*s++);
}

// Function to display an unsigned integer on the LCD
void u32LCD(unsigned int n)
{
 // i is the array index; a stores individual digits
 int i=0;unsigned char a[10];

 // Check whether the number is zero
 if(n==0)
 {
 // Display zero directly
 charLCD('0');
 }
 else
 {
 // Extract digits one by one from the number
 while(n>0)
 {
  // Extract last digit and convert it into ASCII
  a[i++]=(n%10)+48;

  // Remove the last digit from the number
  n=n/10;
  }

  // Start from the last stored digit
  for(--i;i>=0;i--)
  {
  // Display digits in reverse extraction order
  charLCD(a[i]);
  }
 }
}

// Function to display a signed integer on the LCD
void s32LCD(int n)
{
 // Check whether the number is negative
 if(n<0)
 {
 // Display minus sign
 charLCD('-');

 // Convert negative number into positive number
 n=-n;
 }

 // Display the number using unsigned integer function
 u32LCD(n);
}

// Function to display a floating-point number on the LCD
void f32LCD(float fn,unsigned char ndp)
{
 // n stores integer part; i is used for decimal digit count
 unsigned int n,i;

 // Check whether the floating-point number is negative
 if(fn<0)
 {
 // Display minus sign
 charLCD('-');

 // Convert negative number into positive number
 fn=-fn;
 }

 // Extract integer part of floating-point number
 n=fn;

 // Display integer part
 u32LCD(n);

 // Display decimal point
 charLCD('.');

 // Repeat for the required number of decimal places
 for(i=0;i<ndp;i++)
 {
 // Remove integer part and multiply fractional part by 10
 fn=(fn-n)*10;

 // Extract next decimal digit
 n=fn;

 // Convert digit into ASCII and display
 charLCD(n+48);
 }
}

// Function to create custom characters in LCD CGRAM
void buildCGRAM(unsigned char *p,unsigned char nbytes)
{
 // i is used to access each custom character byte
 unsigned int i;

 // Select the starting address of CGRAM
 cmdLCD(GOTO_CGRAM_START);

 // Set RW = 0 to select write mode
 IOCLR0=1<<LCD_RW;

 // Set RS = 1 to select data register
 IOSET0=1<<LCD_RS;

 // Loop through the given number of bytes
 for(i=0;i<nbytes;i++)
 {
  // Send each byte of custom character pattern to LCD
  writeLCD(p[i]);
  }

  // Move LCD cursor back to the beginning of first line
  cmdLCD(GOTO_LINE1_POS0);
}
