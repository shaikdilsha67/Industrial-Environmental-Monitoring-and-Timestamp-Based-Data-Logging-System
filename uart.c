#include <LPC21xx.h>         // Includes LPC2148 register definitions
#include "uart_defines.h"    // Includes UART pin configurations, bit positions, and baud-rate divisor macros
#include "types.h"           // Includes user-defined data types such as u8, u32, s8, s32, and f32


// Function to initialize UART0
void uart_init(void)
{
        PINSEL0&=~((3<<2)|(3<<0));     // Clears function-selection bits for TXD0 and RXD0 pins
        PINSEL0|= txd0_pin_func|rxd0_pin_func; // Selects UART0 functions for TXD0 and RXD0 pins

        U0LCR=((1<<dlab_bit)| (3<<word_len_sel_bits)); // Enables DLAB and selects 8-bit data length
        U0DLL=divisor;                  // Loads the lower 8 bits of the baud-rate divisor into DLL
        U0DLM=divisor>>8;               // Loads the upper 8 bits of the baud-rate divisor into DLM

        U0LCR&=~(1<<dlab_bit);           // Clears DLAB to access UART data registers normally
}


// Function to transmit one byte through UART0
void uart_tx(u8 sdat)
{
        U0THR=sdat;                     // Places the data byte into UART0 transmit holding register
        while(((U0LSR>>temt_bit)&1)==0); // Waits until the transmitter empty condition is reached
}


// Function to receive one byte through UART0
u8 uart_rx(void)
{
        while(((U0LSR>>dr_bit)&1)==0);   // Waits until the data ready (DR) bit becomes 1
        return U0RBR;                     // Reads and returns the received byte from UART0
}


// Function to transmit a string through UART0
void u0_txstr(s8 *s)
{
        while(*s)                         // Continues until the null character '\0' is reached
                uart_tx(*s++);             // Transmits the current character and advances the pointer
}


// Function to transmit an unsigned 32-bit integer through UART0
void u0_txu32(u32 n)
{
        s32 i=0;                          // Index used to store digits in the array
        u8 a[10];                          // Array to store individual decimal digits as ASCII characters
        if(n==0)                            // Checks whether the number is zero
        {
                uart_tx('0');                 // Transmits character 0 directly
        }
        else                                  // Executes when the number is non-zero
        {
                while(n>0)                     // Extracts digits until the number becomes zero
                {
                        a[i++]=(n%10)+48;       // Extracts the last digit and converts it to ASCII
                        n=n/10;                  // Removes the last digit from the number
                }
                for(--i;i>=0;i--)               // Traverses the stored digits in reverse order
                {
                        uart_tx(a[i]);            // Transmits digits in correct order
                }
        }
}


// Function to transmit a signed 32-bit integer through UART0
void u0_txs32(s32 n)
{
        if(n<0)                                // Checks whether the number is negative
        {
                uart_tx('-');                    // Transmits the minus sign
                n=-n;                             // Converts the negative value to positive
        }
        u0_txu32(n);                             // Transmits the number using unsigned integer function
}


// Function to transmit a floating-point number through UART0
void u0_txf32(f32 fn,u8 ndp)
{
        u32 n,i;                                  // n stores integer part; i counts decimal places
        if(fn<0.0)                                 // Checks whether the floating-point number is negative
        {
                uart_tx('-');                        // Transmits minus sign
                fn=-fn;                               // Converts negative value to positive
        }
        n=fn;                                         // Extracts the integer part of the floating-point value
        u0_txu32(n);                                  // Transmits the integer part
        uart_tx('.');                                  // Transmits decimal point
        for(i=0;i<ndp;i++)                            // Repeats for the requested decimal places
        {
                fn=(fn-n)*10;                            // Extracts the next decimal digit
                n=fn;                                     // Stores the digit's integer value
                uart_tx(n+48);                             // Converts digit to ASCII and transmits it
        }
}


// Function to receive a string through UART0
s8* u0_rxstr(void)
{
        static s8 rbuff[100];                           // Static buffer to store received characters
        s8 t,i=0;                                       // t stores received character; i tracks buffer index
        while(1)                                          // Continuously receives characters until Enter/newline
        {
                t=uart_rx();                                // Receives one character from UART
                rbuff[i]=t;                                   // Stores the received character in the buffer
                uart_tx(t);                                   // Echoes the received character back to the terminal

                if((t=='\n')||(t=='\r'))                    // Checks for newline or carriage return
                {
                        rbuff[i]='\0';                         // Replaces line-ending character with string terminator
                        break;                                 // Exits the receiving loop
                }
                i++;                                           // Advances to the next buffer position
         }

        u0_txstr("\n\r");                                    // Transmits newline and carriage return
         return rbuff;                                        // Returns the address of the received string
}
