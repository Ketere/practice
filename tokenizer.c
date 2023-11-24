#include "shell.h"
/**
 * **split_string - splits a string into words. Repeat delimiters are ignored
 * @input_string: the input string
 * @delimiter_string: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **split_string(char *input_string, char *delimiter_string) {
    int index_i, index_j, index_k, index_m, word_count = 0;
    char **result_array;

    if (input_string == NULL || input_string[0] == '\0')
        return (NULL);
    if (!delimiter_string)
        delimiter_string = " ";

    for (index_i = 0; input_string[index_i] != '\0'; index_i++)
        if (!is_delimiter(input_string[index_i], delimiter_string) &&
            (is_delimiter(input_string[index_i + 1], delimiter_string) || !input_string[index_i + 1]))
            word_count++;

    if (word_count == 0)
        return (NULL);

    result_array = malloc((1 + word_count) * sizeof(char *));
    if (!result_array)
        return (NULL);

    for (index_i = 0, index_j = 0; index_j < word_count; index_j++) {
        while (is_delimiter(input_string[index_i], delimiter_string))
            index_i++;

        index_k = 0;
        while (!is_delimiter(input_string[index_i + index_k], delimiter_string) &&
               input_string[index_i + index_k]) {
            index_k++;
        }

        result_array[index_j] = malloc((index_k + 1) * sizeof(char));
        if (!result_array[index_j]) {
            for (index_k = 0; index_k < index_j; index_k++)
                free(result_array[index_k]);
            free(result_array);
            return (NULL);
        }

        for (index_m = 0; index_m < index_k; index_m++)
            result_array[index_j][index_m] = input_string[index_i++];

        result_array[index_j][index_m] = '\0';
    }
    result_array[index_j] = NULL;
    return (result_array);
}

/**
 * **split_string2 - splits a string into words
 * @input_string: the input string
 * @delimiter_char: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **split_string2(char *input_string, char delimiter_char) {
    int index_i, index_j, index_k, index_m, word_count = 0;
    char **result_array;

    if (input_string == NULL || input_string[0] == '\0')
        return (NULL);

    for (index_i = 0; input_string[index_i] != '\0'; index_i++)
        if ((input_string[index_i] != delimiter_char && input_string[index_i + 1] == delimiter_char) ||
            (input_string[index_i] != delimiter_char && !input_string[index_i + 1]) || input_string[index_i + 1] == delimiter_char)
            word_count++;

    if (word_count == 0)
        return (NULL);

    result_array = malloc((1 + word_count) * sizeof(char *));
    if (!result_array)
        return (NULL);

    for (index_i = 0, index_j = 0; index_j < word_count; index_j++) {
        while (input_string[index_i] == delimiter_char && input_string[index_i] != delimiter_char)
            index_i++;

        index_k = 0;
        while (input_string[index_i + index_k] != delimiter_char && input_string[index_i + index_k] &&
               input_string[index_i + index_k] != delimiter_char)
            index_k++;

        result_array[index_j] = malloc((index_k + 1) * sizeof(char));
        if (!result_array[index_j]) {
            for (index_k = 0; index_k < index_j; index_k++)
                free(result_array[index_k]);
            free(result_array);
            return (NULL);
        }

        for (index_m = 0; index_m < index_k; index_m++)
            result_array[index_j][index_m] = input_string[index_i++];

        result_array[index_j][index_m] = '\0';
    }
    result_array[index_j] = NULL;
    return (result_array);
}
