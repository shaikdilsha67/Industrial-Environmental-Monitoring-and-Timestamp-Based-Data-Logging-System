#include <LPC21xx.h>       // Includes LPC2148 register definitions
#include "types.h"         // Includes user-defined data types such as u32
#include "interrupt.h"     // Includes interrupt-related declarations


volatile int set_time_flag; // Global flag shared between ISR and main program
                            // volatile prevents the compiler from assuming its value never changes unexpectedly


// Function to configure External Interrupt 0 (EINT0)
void initEINT0(void)
{
    PINSEL1 &= (u32)~(3<<0);  // Clear bits 0 and 1 to configure the P0.16 pin function
    PINSEL1 |= (1<<0);       // Set bit 0 to select EINT0 function for P0.16

    // VICIntSelect = 0;      // Commented out: selects IRQ mode (0 = IRQ, 1 = FIQ)
                              // If uncommented, it selects IRQ mode for all interrupt sources

    VICIntEnable = 1<<14;    // Enable interrupt source number 14 (EINT0) in VIC

    VICVectCntl0 = (1<<5)|14; // Enable vectored IRQ slot 0 and assign interrupt source 14

    VICVectAddr0 = (u32)eint0_isr; // Store the address of EINT0 ISR in vector slot 0

    EXTINT = 0;              // Clear any pending external interrupt flags

    EXTMODE = 1<<0;         // Configure EINT0 as edge-sensitive interrupt

    EXTPOLAR = 0;            // Select falling-edge polarity for EINT0

}


// Interrupt Service Routine for External Interrupt 0
void eint0_isr(void) __irq
{
    set_time_flag = 1;      // Set flag to inform main program that interrupt occurred
                            // Main program can use this flag to enter time-setting mode

    EXTINT = 1<<0;         // Clear EINT0 interrupt flag by writing 1 to bit 0

    VICVectAddr = 0;        // Signal the VIC that the interrupt service routine has finished
                            // Allows the VIC to handle the next interrupt
}
