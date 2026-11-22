#include "types.h"     // Include user-defined data types such as u8, s32, f32
#include "adc.h"      // Include ADC function declarations


// Function to read LM35 temperature in Celsius
// tdegc = pointer to store temperature in degree Celsius
void read_lm35(u8 *tdegc)
{
 static s32 flag;     // Static variable retains its value between function calls
 u16 dval;            // Variable to store ADC digital value
 f32 eAR;             // Variable to store calculated analog voltage

 // Check whether ADC is initialized or not
 if(flag==0)
 {
  // Initialize ADC only during the first function call
  init_adc();

  // Set flag to 1 so ADC initialization is not repeated
  flag=1;
  }

  // Read ADC channel 1 and store digital value in dval and voltage in eAR
  read_adc(1,&dval,&eAR);

  // Convert LM35 output voltage into temperature in Celsius
  // LM35 output = 10mV per degree Celsius
  // Multiplying voltage by 100 converts volts into degree Celsius
  *tdegc=(eAR*100);

}


// Function to read LM35 temperature using two ADC channels
// tdegc = pointer to store temperature in Celsius
// tdegf = pointer to store temperature in Fahrenheit
void read_lm35NP(f32 *tdegc,f32 *tdegf)
{
 // Variables to store digital values from two ADC channels
 u16 dval1,dval2;

 // Variables to store analog voltages from two ADC channels
 f32 eAR1,eAR2;

 // Static flag to ensure ADC initializes only once
 static s32 flag;

 // Check whether ADC is initialized
 if(flag==0)
 {
  // Initialize ADC peripheral
  init_adc();

  // Mark ADC as initialized
  flag=1;
 }

 // Read ADC channel 1 and store digital value and voltage
 read_adc(1,&dval1,&eAR1);

 // Read ADC channel 2 and store digital value and voltage
 read_adc(2,&dval2,&eAR2);

 // Calculate temperature in Celsius using the difference between two voltages
 // (eAR1 - eAR2) gives differential voltage
 // Multiplying by 100 converts voltage difference into Celsius
 *tdegc=((eAR1-eAR2)*100);

 // Convert Celsius into Fahrenheit
 // Formula: Fahrenheit = (Celsius * 9/5) + 32
 *tdegf=((*tdegc * (9/5.0))+32);

}
