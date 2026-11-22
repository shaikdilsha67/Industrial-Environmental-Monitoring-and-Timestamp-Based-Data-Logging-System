unsigned int colscan(void);
// Function prototype for colscan().
// Checks whether any key is pressed by reading the keypad column pins.
// Returns an unsigned integer (0 or 1).

unsigned int rowcheck(void);
// Function prototype for rowcheck().
// Identifies which row contains the pressed key.
// Returns the row number (0 to 3).

unsigned int colcheck(void);
// Function prototype for colcheck().
// Identifies which column contains the pressed key.
// Returns the column number (0 to 3).

unsigned int keyscan(void);
// Function prototype for keyscan().
// Scans the keypad and returns the value of the pressed key.

void initkpm(void);
// Function prototype for initkpm().
// Configures the keypad row pins as outputs and column pins as inputs.
// Does not return any value (void).
