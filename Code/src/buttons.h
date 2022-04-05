#ifndef BUTTONS_H
#define BUTTONS_H


#define ROW_COUNT 3
#define COL_COUNT 8
#define BUTTON_COUNT (COL_COUNT * ROW_COUNT)

void config_buttons();

unsigned char get_button_states();

void enable_all_rows();

void handle_buttons();
unsigned char buttons_ready();
unsigned char button_debounced(unsigned char row, unsigned char col);
unsigned char is_button_pressed(unsigned char row, unsigned char col);



#endif /* ifndef BUTTONS_H */