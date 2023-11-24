#include "shell.h"
/**
 * checkDelimiter - test if current char in buffer is a chain delimiter
 * @information: the parameter struct
 * @buffer: the char buffer
 * @position: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */

int checkDelimiter(info_t *information, char *buffer, size_t *position) {
    size_t index = *position;

    if (buffer[index] == '|' && buffer[index + 1] == '|') {
        buffer[index] = 0;
        index++;
        information->cmd_buf_type = CMD_OR;
    } else if (buffer[index] == '&' && buffer[index + 1] == '&') {
        buffer[index] = 0;
        index++;
        information->cmd_buf_type = CMD_AND;
    } else if (buffer[index] == ';') {
        buffer[index] = 0;
        information->cmd_buf_type = CMD_CHAIN;
    } else {
        return (0);
    }
    *position = index;
    return (1);
}

/**
 * processChain - checks whether to continue chaining based on last status
 * @information: the parameter struct
 * @buffer: the char buffer
 * @position: address of current position in buf
 * @start: starting position in buf
 * @length: length of buf
 *
 * Return: Void
 */

void processChain(info_t *information, char *buffer, size_t *position, size_t start, size_t length) {
    size_t index = *position;

    if (information->cmd_buf_type == CMD_AND) {
        if (information->status) {
            buffer[start] = 0;
            index = length;
        }
    }
    if (information->cmd_buf_type == CMD_OR) {
        if (!information->status) {
            buffer[start] = 0;
            index = length;
        }
    }

    *position = index;
}

/**
 * substituteAlias - replaces an alias in the tokenized string
 * @information: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int substituteAlias(info_t *information) {
    int i;
    list_t *node;
    char *pointer;

    for (i = 0; i < 10; i++) {
        node = search_starts_with(information->alias, information->argv[0], '=');
        if (!node)
            return (0);
        free(information->argv[0]);
        pointer = _strchr(node->str, '=');
        if (!pointer)
            return (0);
        pointer = _strdup(pointer + 1);
        if (!pointer)
            return (0);
        information->argv[0] = pointer;
    }
    return (1);
}

/**
 * substituteVariables - replaces variables in the tokenized string
 * @information: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int substituteVariables(info_t *information) {
    int i = 0;
    list_t *node;

    for (i = 0; information->argv[i]; i++) {
        if (information->argv[i][0] != '$' || !information->argv[i][1])
            continue;

        if (!_strcmp(information->argv[i], "$?")) {
            replace_string(&(information->argv[i]),
                    _strdup(convert_number(information->status, 10, 0)));
            continue;
        }
        if (!_strcmp(information->argv[i], "$$")) {
            replace_string(&(information->argv[i]),
                    _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        node = search_starts_with(information->env, &information->argv[i][1], '=');
        if (node) {
            replace_string(&(information->argv[i]),
                    _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        replace_string(&information->argv[i], _strdup(""));
    }
    return (0);
}

/**
 * replaceString - replaces string
 * @oldString: address of old string
 * @newString: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replaceString(char **oldString, char *newString) {
    free(*oldString);
    *oldString = newString;
    return (1);
}
