extern volatile int set_time_flag;
// Declares that set_time_flag is a global variable defined in another C file.
// volatile: Its value can change unexpectedly, such as inside an interrupt (ISR).
// extern: Allows this file to access the variable without defining a new one.

void initEINT0(void);
// Function prototype for initEINT0().
// Used to configure and enable External Interrupt 0 (EINT0).
// void: The function does not return any value.
// void inside (): The function takes no arguments.

void eint0_isr(void) __irq;
// Function prototype for the EINT0 interrupt service routine (ISR).
// __irq: Specifies that this function is an interrupt handler.
// This function executes when the configured external interrupt occurs.
