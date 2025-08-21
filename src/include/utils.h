#ifndef UTILS_H
#define UTILS_H

#define BACKSPACE_KEY 127
#define ESCAPE_CHAR '\x1b'
#define UP_ARROW_KEY 'A'
#define DOWN_ARROW_KEY 'B'
#define CLEAR_LINE "\33[2K\r"
#define STR_TOKEN_DELIM " \t\n"

void enable_raw_mode(struct termios *original);
void disable_raw_mode(struct termios *original);

#endif