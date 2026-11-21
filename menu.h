#include "types.h"

u32 Menu_top(void);       // Function declaration: displays the main menu and returns the selected key
void Menu(void);          // Function declaration: displays and handles the RTC submenu
void time_menu(void);     // Function declaration: displays the time-setting menu
void date_menu(void);     // Function declaration: displays the date-setting menu

void set_hours(void);    // Function declaration: sets the RTC hours value
void set_minutes(void);  // Function declaration: sets the RTC minutes value
void set_seconds(void);  // Function declaration: sets the RTC seconds value

void set_date(void);     // Function declaration: sets the RTC date (day)
void set_month(void);   // Function declaration: sets the RTC month
void set_year(void);    // Function declaration: sets the RTC year
void set_temp_limit(void); // Function declaration: sets the temperature threshold
