#ifndef PARSE_STR_H
#define PARSE_STR_H

#include <ctype.h>
#include <stdbool.h>


bool is_line_empty_or_whitespace(const char *);
void trim_whitespace_inplace(char *);
void remove_trailing_char(char *, char);
void remove_leading_char(char *, char);
bool starts_with(char *, char);
bool ends_with(char *, char);

#endif