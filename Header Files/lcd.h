// Sends one byte (command or data) to the LCD
void writeLCD(unsigned char byte);

// Sends a command instruction to the LCD
void cmdLCD(unsigned char cmd);

// Initializes the LCD (configuration, display ON, clear display, etc.)
void initLCD(void);

// Displays one ASCII character on the LCD
void charLCD(unsigned char asciival);

// Displays a string of characters on the LCD
void strLCD(char *s);

// Displays an unsigned integer number on the LCD
void u32LCD(unsigned int);

// Displays a signed integer number (positive or negative) on the LCD
void s32LCD(int);

// Displays a floating-point number with the specified decimal places
void f32LCD(float, unsigned char ndp);

// Creates custom characters in LCD CGRAM using the given pattern and byte count
void buildCGRAM(unsigned char *p, unsigned char nBytes);

// Generates a delay in milliseconds for the specified duration
void delay_ms(unsigned int ch);
