#ifndef PARSE_STR_H
#define PARSE_STR_H

#include <ctype.h>
#include <stdbool.h>

/**
 * Checks if the given string starts with the specified character.
 *
 * @param string The input string to check.
 * @param ch The character to check at the start of the string.
 * @return true if the string starts with the character `ch`, false otherwise.
 */
bool starts_with(char *string, char ch);

/**
 * Converts the string pointed to by `str` to uppercase in place.
 *
 * @param str Pointer to a char pointer string to convert to uppercase.
 *            If `str` or `*str` is NULL, does nothing.
 */
void to_upper(char **str);

/**
 * Reverses the characters in the string up to the given length.
 *
 * @param str The string to reverse.
 * @param length The number of characters in the string to reverse.
 */
static void reverse_str(char *str, int length);

/**
 * Converts an integer to its string representation.
 *
 * Dynamically allocates memory for the resulting string,
 * which should be freed by the caller.
 *
 * @param num The integer number to convert.
 * @return A dynamically allocated string representing the integer,
 *         or NULL if memory allocation fails.
 */
char *itoa_dynamic(int num);

/**
 * Checks if the given string contains only digit characters.
 *
 * @param str The string to check.
 * @return true if the string contains only digits, false otherwise.
 */
bool is_digits_only(const char *str);

/**
 * Checks if the given string is surrounded by matching braces.
 *
 * Supports the following pairs: [], {}, ().
 * Calls `segmentation_fault_error()` if an invalid brace character is passed.
 *
 * @param string The string to check.
 * @param ch The opening brace character to check for.
 * @return true if the string starts and ends with the matching brace
 * characters.
 */
bool surrounded_by_braces(char *string, char ch);

/**
 * Checks if the given string ends with the specified character.
 *
 * @param string The input string to check.
 * @param ch The character to check at the end of the string.
 * @return true if the string ends with the character `ch`, false otherwise.
 */
bool ends_with(char *string, char ch);

/**
 * Removes the trailing character `c` from the string if it exists.
 *
 * @param string The string to modify.
 * @param c The trailing character to remove.
 */
void remove_trailing_char(char *string, char c);

/**
 * Removes the leading character `ch` from the string if it exists.
 *
 * @param str The string to modify.
 * @param ch The leading character to remove.
 */
void remove_leading_char(char *str, char ch);

/**
 * Checks if the input string is empty or contains only whitespace characters.
 *
 * @param string The string to check.
 * @return true if the string is empty or contains only whitespace, false
 * otherwise.
 */
bool is_line_empty_or_whitespace(const char *string);

/**
 * Trims leading and trailing whitespace from the string.
 *
 * Note: This function adjusts the pointer to the first non-whitespace
 * character and modifies the original string by adding a null terminator.
 *
 * @param string The string to trim.
 */
void trim_whitespace(char *string);

/**
 * Trims leading and trailing whitespace from the string in place.
 *
 * This function modifies the original string by shifting it left if needed
 * and replacing trailing whitespace characters with null terminators.
 *
 * @param string The string to trim in place.
 */
void trim_whitespace_inplace(char *string);

#endif