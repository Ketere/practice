#include "shell.h"
/**
 * _copy_string - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *_copy_string(char *destination, char *source) {
    int index = 0;

    if (destination == source || source == NULL)
        return (destination);

    while (source[index]) {
        destination[index] = source[index];
        index++;
    }
    destination[index] = '\0';
    return (destination);
}

/**
 * _duplicate_string - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_duplicate_string(const char *string) {
    int length = 0;
    char *result;

    if (string == NULL)
        return (NULL);

    while (*string++)
        length++;

    result = malloc(sizeof(char) * (length + 1));
    if (!result)
        return (NULL);

    for (length++; length--;) {
        result[length] = *--string;
    }
    return (result);
}

/**
 * _print_string - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _print_string(char *string) {
    int index = 0;

    if (!string)
        return;

    while (string[index] != '\0') {
        _write_character(string[index]);
        index++;
    }
}

/**
 * _write_character - writes the character c to stdout
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _write_character(char character) {
    static int index;
    static char buffer[WRITE_BUFFER_SIZE];

    if (character == FLUSH_BUFFER || index >= WRITE_BUFFER_SIZE) {
        write(1, buffer, index);
        index = 0;
    }
    if (character != FLUSH_BUFFER)
        buffer[index++] = character;
    return (1);
}
