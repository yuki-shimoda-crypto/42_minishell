/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 23:26:00 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/08 19:59:35 by enogaWa          ###   ########.fr       */
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
    write(STDERR_FILENO, word, strlen(word));
    write(STDERR_FILENO, msg, strlen(msg));
    g_return_error.exec_error = true;
}