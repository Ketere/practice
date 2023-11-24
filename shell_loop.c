#include "shell.h"

/**
 * shell_loop - main shell loop
 * @shell_info: shell information struct
 * @arguments: arguments from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(shell_info_t *shell_info, char **arguments)
{
	ssize_t read_result = 0;
	int builtin_result = 0;

	while (read_result != -1 && builtin_result != -2)
	{
		clear_shell_info(shell_info);
		if (prompt_user(shell_info))
			print_string("simple_shell:~$ ");
		else
			print_char(BUF_FLUSH);
		read_result = get_user_input(shell_info);
		if (read_result != -1)
		{
			set_shell_info(shell_info, arguments);
			builtin_result = find_builtin_command(shell_info);
			if (builtin_result == -1)
				find_executable_command(shell_info);
		}
		else if (prompt_user(shell_info))
			print_char('\n');
		free_memory(shell_info, 0);
	}
	write_history_file(shell_info);
	free_memory(shell_info, 1);
	if (!prompt_user(shell_info) && shell_info->status)
		exit(shell_info->status);
	if (builtin_result == -2)
	{
		if (shell_info->error_num == -1)
			exit(shell_info->status);
		exit(shell_info->error_num);
	}
	return (builtin_result);
}

/**
 * find_builtin_command - finds a builtin command
 * @shell_info: shell information struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */

int find_builtin_command(shell_info_t *shell_info)
{
	int i, built_in_result = -1;
	builtin_table_t builtintable[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintable[i].type; i++)
		if (string_compare(shell_info->arguments[0], builtintable[i].type) == 0)
		{
			shell_info->line_count++;
			built_in_result = builtintable[i].func(shell_info);
			break;
		}
	return (built_in_result);
}


/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */


void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((tonny(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */


void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_this(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
