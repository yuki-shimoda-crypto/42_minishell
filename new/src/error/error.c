/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 23:26:00 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/14 14:08:23 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <unistd.h>

// ok
void	assert_error(const char *msg)
{
	if (msg)
	{
		write(STDERR_FILENO, ERROR_ASSERT, strlen(ERROR_ASSERT));
		write(STDERR_FILENO, msg, strlen(msg));
	}
	exit(1);
}

// ok
void	syntax_error(const char *msg, char **skipped, char *line)
{
	if (msg)
	{
		write(STDERR_FILENO, ERROR_SYNTAX, strlen(ERROR_SYNTAX));
		write(STDERR_FILENO, msg, strlen(msg));
	}
	while (*line)
		line++;
	*skipped = line;
}

void	file_exec_error(const char *word, const char *msg)
{
    write(STDERR_FILENO, ERROR_EXEC, strlen(ERROR_EXEC));
    write(STDERR_FILENO, word, strlen(word));
    write(STDERR_FILENO, msg, strlen(msg));
    g_return_error.exec_error = true;
}

void	export_error(const char *cmd)
{
	write(STDERR_FILENO, PROMPT_ERROR, strlen(PROMPT_ERROR));
	write(STDERR_FILENO, "export: `", strlen("export: `"));
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, "': not a valid identifier\n", strlen("': not a valid identifier\n"));
}
