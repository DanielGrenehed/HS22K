#ifndef KEY_INPUT_H
#define KEY_INPUT_H

void config_input();

unsigned char get_button_states();

void enable_all_rows();
void clear_all_rows();

void handle_button_matrix();

unsigned char is_button_debounced(unsigned char row, unsigned char col);
unsigned char is_button_pressed(unsigned char row, unsigned char col);

#endif /* ifndef KEY_INPUT_H */