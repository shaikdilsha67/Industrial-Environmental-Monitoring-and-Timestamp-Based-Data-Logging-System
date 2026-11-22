// Function declaration to initialize the RTC peripheral
void initRTC(void);

// Function declaration to set RTC seconds, minutes, hours, date, month, and year
void set_rtc(u32 *s,u32 *m,u32 *h,u32 *d,u32 *mon,u32 *y);

// Function declaration to get time and date from user input using keypad
void set_rtc_input(void);

// Function declaration to read current time and date from RTC registers
// h   = pointer to store hours
// m   = pointer to store minutes
// s   = pointer to store seconds
// d   = pointer to store day
// mon = pointer to store month
// y   = pointer to store year
void read_rtc_values(u32 *h,u32 *m,u32 *s,u32 *d,u32 *mon,u32 *y);
