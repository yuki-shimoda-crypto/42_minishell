/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 04:04:00 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 14:14:18 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <unistd.h>

void	assert_error(const char *msg)
{
	if (msg)
	{
		write(STDERR_FILENO, ERROR_ASSERT, ft_strlen(ERROR_ASSERT));
		write(STDERR_FILENO, msg, ft_strlen(msg));
	}
	exit(1);
}

void	syntax_error(const char *msg, char **skipped, char *line)
{
	if (msg)
	{
		write(STDERR_FILENO, ERROR_SYNTAX, ft_strlen(ERROR_SYNTAX));
		write(STDERR_FILENO, msg, ft_strlen(msg));
	}
	while (*line)
		line++;
	*skipped = line;
	g_return_error.return_value = 258;
}

void	file_exec_error(const char *word, const char *msg)
{
	write(STDERR_FILENO, ERROR_EXEC, ft_strlen(ERROR_EXEC));
	write(STDERR_FILENO, word, ft_strlen(word));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	g_return_error.error = true;
}
