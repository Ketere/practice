#include "shell.h"

/**
 * is_executable - checks if a file is an executable command
 * @data: the program's data
 * @file_path: path to the file
 *
 * Returns: 1 if true, 0 otherwise
 */

int is_executable(data_of_program *data, char *file_path)
{
    struct stat file_stat;

    (void)data;
    if (!file_path || stat(file_path, &file_stat))
        return (0);

    if (file_stat.st_mode & S_IFREG)
        return (1);

    return (0);
}

/**
 * copy_chars - duplicates characters from a string within a specific range
 * @source: the source string
 * @start: starting index
 * @end: ending index
 *
 * Returns: pointer to a new buffer
 */

char *copy_chars(char *source, int start, int end)
{
    static char buffer[1024];
    int i = 0, j = 0;

    for (j = 0, i = start; i < end; i++)
        if (source[i] != ':')
            buffer[j++] = source[i];
    buffer[j] = '\0';
    return (buffer);
}

/**
 * find_command_in_path - finds the command in the PATH environment variable
 * @data: the program's data
 * @path_str: the PATH environment variable string
 * @command: the command to find
 *
 * Returns: full path of the command if found, otherwise NULL
 */

char *find_command_in_path(data_of_program *data, char *path_str, char *command)
{
    int i = 0, curr_position = 0;
    char *full_path;

    if (!path_str)
        return (NULL);
    if ((_strlen(command) > 2) && starts_with(command, "./"))
    {
        if (is_executable(data, command))
            return (command);
    }
    while (1)
    {
        if (!path_str[i] || path_str[i] == ':')
        {
            full_path = copy_chars(path_str, curr_position, i);
            if (!*full_path)
                _strcat(full_path, command);
            else
            {
                _strcat(full_path, "/");
                _strcat(full_path, command);
            }
            if (is_executable(data, full_path))
                return (full_path);
            if (!path_str[i])
                break;
            curr_position = i;
        }
        i++;
    }
    return (NULL);
}
