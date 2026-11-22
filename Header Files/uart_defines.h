#define txd0_pin_func 0x00000001  // Selects TXD0 function for the UART0 transmit pin (P0.0)

#define rxd0_pin_func 0x00000004  // Selects RXD0 function for the UART0 receive pin (P0.1)

#define baud 9600                  // Defines UART communication speed as 9600 bits per second
#define fosc 12000000             // Defines oscillator frequency as 12 MHz
#define cclk (fosc*5)             // Defines CPU clock: FOSC × 5 = 60 MHz
#define pclk (cclk/4)             // Defines peripheral clock: CCLK ÷ 4 = 15 MHz
#define divisor (pclk/(16*baud))   // Calculates UART baud-rate divisor: PCLK ÷ (16 × baud)


#define _8bit 3;                  // Defines the value used to select 8-bit data length (semicolon is part of this macro)
#define word_len_sel_bits 0       // Defines the starting bit position of the word-length selection field in U0LCR
#define dlab_bit 7                // Defines bit 7 of U0LCR (Divisor Latch Access Bit)

#define temt_bit 6                // Defines bit 6 of U0LSR (Transmitter Empty bit)
#define dr_bit 0                  // Defines bit 0 of U0LSR (Data Ready bit)
