#include "types.h"  // Include user-defined data types such as u8, u16, f32

// Function declaration for initializing the ADC peripheral
void init_adc(void);

// Function declaration for reading ADC data from a selected channel
// chno = ADC channel number
// dval = pointer to store the digital ADC value
// eAR  = pointer to store the calculated analog voltage
void read_adc(u8 chno,u16 *dval,f32 *eAR);
