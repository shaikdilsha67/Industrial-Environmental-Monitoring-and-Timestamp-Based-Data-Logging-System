#include "types.h"             // User-defined data types like u8, u16, f32
#include <LPC21xx.h>          // LPC2148 register definitions
#include "adc_defines.h"      // ADC bit positions and configuration macros
#include "lcd.h"              // LCD function declarations

// Function to initialize ADC peripheral
void init_adc(void)
{
        // Configure pins P0.28 to P0.30 for ADC-related functions
        // Using PINSEL register to select the required pin function

        // Clear bits 24 and 25 of PINSEL1
        // P0.28 is configured for ADC function (AD0.1)
        PINSEL1&=~(3 << 24);

        // Select ADC function for P0.28 using AIN1_FUNC macro
        PINSEL1|=AIN1_FUNC;

        // Configure ADCR (ADC Control Register)

        // Set PDN bit to power ON ADC
        // Set CLKDIV to configure ADC clock division
        ADCR|=(1<<PDN_BIT)|(CLKDIV_VAL<<CLKDIV_BITS);
}

// Function to read ADC value from selected channel
// chno = ADC channel number
// dval = pointer to store digital ADC value
// eAR  = pointer to store equivalent analog voltage
void read_adc(u8 chno,u16 *dval,f32 *eAR)
{
        // Clear the channel selection bits (bits 0 to 7)
        // This allows us to select a new ADC channel
        ADCR&=0xFFFFFF00;

        // Select the ADC channel and start ADC conversion
        ADCR|=(1<<ADC_CONV_START_BIT)|(1<<chno);

        // Wait for 30 milliseconds for conversion
        delay_ms(30);

        // Wait until DONE bit becomes 1
        // DONE = 1 means ADC conversion is completed
        while(((ADDR>>DONE_BIT)&1)==0);

        // Clear START bits after conversion is completed
        // Stop the conversion start command
        ADCR&=~(1<<ADC_CONV_START_BIT);

        // Extract the 10-bit digital ADC result from ADDR register
        // Store the digital value in the memory pointed by dval
        *dval=((ADDR>>DIGITAL_DATA_BITS)&1023);

        // Convert digital ADC value into analog voltage
        // ADC resolution = 10 bits (0 to 1023)
        // Reference voltage = 3.3V
        *eAR=*dval*(3.3/1023);
}