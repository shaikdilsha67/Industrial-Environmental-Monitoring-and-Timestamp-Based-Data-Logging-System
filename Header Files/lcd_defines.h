// Clear all characters from the LCD display and set cursor to position 0
#define CLEAR_LCD 0x01

// Return cursor to home position (first position of line 1)
#define RET_CUR_HOME 0x02

// Move cursor one position to the right after writing a character
#define SHIFT_CUR_RIGHT 0x06

// Move cursor one position to the left
#define SHIFT_CUR_LEFT 0x07

// Turn OFF the LCD display
#define DSP_OFF 0x08

// Turn ON display and turn OFF cursor
#define DSP_ON_CUR_OFF 0x0C

// Turn ON display and cursor
#define DSP_ON_CUR_ON 0x0E

// Turn ON display, cursor, and cursor blinking
#define DSP_ON_CUR_BLINK 0x0F

// Shift entire display to the left
#define SHIFT_DISP_LEFT 0x10

// Shift entire display to the right
#define SHIFT_DISP_RIGHT 0x14

// Configure LCD for 8-bit data mode and 1 line
#define MODE_8BIT_1LINE 0x30

// Configure LCD for 4-bit data mode and 1 line
#define MODE_4BIT_1LINE 0x20

// Configure LCD for 8-bit data mode and 2 lines
#define MODE_8BIT_2LINE 0x38

// Configure LCD for 4-bit data mode and 2 lines
#define MODE_4BIT_2LINE 0x28

// Set cursor to first position of line 1
#define GOTO_LINE1_POS0 0x80

// Set cursor to first position of line 2
#define GOTO_LINE2_POS0 0xC0

// Set cursor to first position of line 3 (20x4 LCD)
#define GOTO_LINE3_POS0 0x94

// Set cursor to first position of line 4 (20x4 LCD)
#define GOTO_LINE4_POS0 0xD4

// Set starting address of CGRAM for creating custom characters
#define GOTO_CGRAM_START 0x40


// LCD connections

// Starting bit position of LCD data pins (D0-D7 connected to P0.8-P0.15 or configured pins)
#define LCD_DATA 8

// Register Select pin: 0 = command, 1 = data
#define LCD_RS 19

// Read/Write pin: 0 = write, 1 = read
#define LCD_RW 17

// Enable pin: pulse this pin to latch data/command into LCD
#define LCD_EN 18
