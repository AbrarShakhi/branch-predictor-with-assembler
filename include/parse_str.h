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
bool surrounded_by_braces(char *, char);
bool is_digits_only(const char *);
void to_upper(char **);
char *itoa_dynamic(int);

#endif