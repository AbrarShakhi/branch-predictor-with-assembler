#include "parse_str.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool starts_with(char *string, char ch) {
	if (!strlen(string)) {
		return false;
	}
	return string[0] == ch;
}


bool ends_with(char *string, char ch) {
	size_t len = strlen(string);
	if (!len) {
		return false;
	}
	return string[len - 1] == ch;
}

void remove_trailing_char(char *string, char c) {
	size_t len = strlen(string);
	if (len > 0 && string[len - 1] == c) {
		string[len - 1] = '\0';
	}
}

void remove_leading_char(char *str, char ch) {
	if (!str)
		return;
	if (str[0] == ch) {
		size_t len = strlen(str);
		memmove(str, str + 1, len);
	}
}


bool is_line_empty_or_whitespace(const char *string) {
	while (*string) {
		if (!isspace((unsigned char)*string)) {
			return false;
		}
		string++;
	}
	return true;
}


void trim_whitespace(char *string) {
	char *end;

	while (isspace((unsigned char)*string)) {
		string++;
	}
	if (*string == 0) {
		*string = '\0';
		return;
	}

	end = string + strlen(string) - 1;
	while (end > string && isspace((unsigned char)*end)) {
		end--;
	}

	*(end + 1) = '\0';
}

void trim_whitespace_inplace(char *string) {
	char *start = string;
	char *end;
	size_t len;

	while (isspace((unsigned char)*start)) {
		start++;
	}
	if (start != string) {
		len = strlen(start);
		memmove(string, start, len + 1);
	}

	len = strlen(string);
	if (len == 0)
		return;

	end = string + len - 1;
	while (end >= string && isspace((unsigned char)*end)) {
		*end = '\0';
		end--;
	}
}
