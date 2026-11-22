// Define the external oscillator frequency as 12 MHz
#define FOSC 12000000

// Define the CPU clock frequency (CCLK)
// CCLK = FOSC * 5 = 60 MHz
#define CCLK (FOSC*5)

// Define the peripheral clock frequency (PCLK)
// PCLK = CCLK / 4 = 15 MHz
#define PCLK (CCLK/4)

// Define the required ADC clock frequency as 3 MHz
#define ADC_CLK 3000000


// Define bit positions for ADCR (ADC Control Register)

// Starting bit position of CLKDIV field in ADCR (bits 8–15)
#define CLKDIV_BITS 8 //8-15

// Bit position of PDN (Power Down) bit in ADCR
#define PDN_BIT 21

// Starting bit position of START field in ADCR (bit 24 onwards)
#define ADC_CONV_START_BIT 24

// Calculate the clock divider value required for ADC
// CLKDIV = (PCLK / ADC_CLK) - 1
#define CLKDIV_VAL ((PCLK/ADC_CLK)-1)


// Define bit positions for ADDR (ADC Data Register)

// Starting bit position of digital ADC result (bits 6–15)
#define DIGITAL_DATA_BITS 6  //6-15

// Bit position of DONE flag in ADDR register
#define DONE_BIT 31


// Define ADC pin function selection values for PINSEL registers

// Select ADC function for AIN0 (AD0.0)
#define AIN0_FUNC 0

// Select ADC function for AIN1 (AD0.1 / P0.28)
#define AIN1_FUNC 0x01000000

// Select ADC function for AIN2 (AD0.2)
#define AIN2_FUNC 0

// Select ADC function for AIN3 (AD0.3)
#define AIN3_FUNC 0
