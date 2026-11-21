#define FOSC  12000000
// Defines the oscillator frequency as 12 MHz (12,000,000 Hz).

#define CCLK  (FOSC * 5)
// Defines the CPU clock (CCLK) as 5 times the oscillator frequency.
// CCLK = 12 MHz * 5 = 60 MHz.

#define PCLK  (CCLK / 4)
// Defines the peripheral clock (PCLK) as one-fourth of CCLK.
// PCLK = 60 MHz / 4 = 15 MHz.
