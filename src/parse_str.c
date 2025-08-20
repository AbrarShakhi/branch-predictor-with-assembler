#include "parse_str.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "bool.h"


bool find_char(char *string, char ch) {
	while (*string) {
		if (*string == ch) {
			return true;
		}
		string++;
	}
	return false;
}

void remove_trailing_char(char *token, char c) {
	size_t len = strlen(token);
	if (len > 0 && token[len - 1] == c) {
		token[len - 1] = '\0';
	}
}

bool is_line_empty_or_whitespace(const char *line) {
	while (*line) {
		if (!isspace((unsigned char)*line)) {
			return false;
		}
		line++;
	}
	return true;
}

#include <ctype.h>
#include <string.h>


void trim_whitespace(char *line) {
	char *end;

	while (isspace((unsigned char)*line)) {
		line++;
	}
	if (*line == 0) {
		*line = '\0';
		return;
	}

	end = line + strlen(line) - 1;
	while (end > line && isspace((unsigned char)*end)) {
		end--;
	}

	*(end + 1) = '\0';
}

void trim_whitespace_inplace(char *line) {
	char *start = line;
	char *end;
	size_t len;

	while (isspace((unsigned char)*start)) {
		start++;
	}
	if (start != line) {
		len = strlen(start);
		memmove(line, start, len + 1);
	}

	len = strlen(line);
	if (len == 0)
		return;

	end = line + len - 1;
	while (end >= line && isspace((unsigned char)*end)) {
		*end = '\0';
		end--;
	}
}
