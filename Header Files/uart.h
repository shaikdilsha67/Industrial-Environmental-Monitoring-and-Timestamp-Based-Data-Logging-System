#include "types.h"  // Includes user-defined data types such as u8, u32, s8, s32, and f32

void uart_init(void);
// Function prototype for uart_init().
// Initializes UART0, configures TXD0/RXD0 pins, and sets the baud rate.

void uart_tx(u8 sdat);
// Function prototype for uart_tx().
// Accepts one byte of data (sdat) and transmits it through UART.

u8 uart_rx(void);
// Function prototype for uart_rx().
// Receives one byte through UART and returns the received data.


void u0_txstr(s8 *s);
// Function prototype for u0_txstr().
// Accepts a pointer to a string and transmits the string through UART0.

void u0_txu32(u32);
// Function prototype for u0_txu32().
// Accepts an unsigned 32-bit integer and transmits it as decimal digits.

void u0_txs32(s32);
// Function prototype for u0_txs32().
// Accepts a signed 32-bit integer and transmits it, including the minus sign if negative.

void u0_txf32(f32,u8);
// Function prototype for u0_txf32().
// Accepts a floating-point number (f32) and the number of decimal places (u8).
// Transmits the floating-point value through UART0.

s8* u0_rxstr(void);
// Function prototype for u0_rxstr().
// Receives a string through UART0 and returns a pointer to the received string.
// s8* means the function returns a pointer to a signed 8-bit character type.
