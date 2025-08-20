#ifndef PARSE_STR_H
#define PARSE_STR_H

#include <ctype.h>

#include "bool.h"


bool is_line_empty_or_whitespace(const char *);
void trim_whitespace_inplace(char *);
void remove_trailing_char(char *, char);
bool find_char(char *, char);

#endif