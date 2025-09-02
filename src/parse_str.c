#include "parse_str.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "miscs.h"

bool starts_with(char *string, char ch) {
  if (!strlen(string)) {
    return false;
  }
  return string[0] == ch;
}

void to_upper(char **str) {
  if (str == NULL || *str == NULL) {
    return;
  }

  char *p = *str;
  while (*p) {
    *p = toupper((unsigned char)*p);
    p++;
  }
}

void reverse_str(char *str, int length) {
  int start = 0;
  int end = length - 1;
  while (start < end) {
    char tmp = str[start];
    str[start] = str[end];
    str[end] = tmp;
    start++;
    end--;
  }
}

char *itoa_dynamic(int num) {
  bool is_negative = false;
  int tmp_num = num;
  int length = 0;

  if (num == 0) {
    char *result = malloc(2);
    if (!result)
      return NULL;
    result[0] = '0';
    result[1] = '\0';
    return result;
  }

  if (num < 0) {
    is_negative = true;
    tmp_num = -num;
  } else {
    tmp_num = num;
  }

  int n = tmp_num;
  while (n > 0) {
    n /= 10;
    length++;
  }

  length += is_negative ? 1 : 0;
  char *str = malloc(length + 1);
  if (!str)
    return NULL;

  int i = 0;
  int val = tmp_num;
  while (val > 0) {
    str[i++] = (val % 10) + '0';
    val /= 10;
  }

  if (is_negative) {
    str[i++] = '-';
  }
  str[i] = '\0';
  reverse_str(str, i);

  return str;
}

bool is_digits_only(const char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

bool surrounded_by_braces(char *string, char ch) {
  switch (ch) {
  case '[':
    return starts_with(string, '[') && ends_with(string, ']');
  case '{':
    return starts_with(string, '{') && ends_with(string, '}');
  case '(':
    return starts_with(string, '(') && ends_with(string, ')');
  default:
    segmentation_fault_error("Invalid operand syntax.");
    return false;
  }
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
