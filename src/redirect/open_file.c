/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:24:18 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/16 12:42:28 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int	open_redir_out(char *filename)
{
	int	fd;

	fd = 0;
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(STDERR_FILENO, PROMPT_ERROR, strlen(PROMPT_ERROR));
		perror(filename);
		g_return_error.redirect_error = true;
		g_return_error.return_value = 1;
	}
	return (fd);
}

int	open_redir_append(char *filename)
{
	int	fd;

	fd = 0;
	fd = open (filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		write(STDERR_FILENO, PROMPT_ERROR, strlen(PROMPT_ERROR));
		perror(filename);
		g_return_error.redirect_error = true;
		g_return_error.return_value = 1;
	}
	return (fd);
}

int	open_redir_in(char *filename)
{
	int	fd;

	fd = 0;
	fd = open (filename, O_RDONLY);
	if (fd == -1)
	{
		write(STDERR_FILENO, PROMPT_ERROR, strlen(PROMPT_ERROR));
		perror(filename);
		g_return_error.redirect_error = true;
		g_return_error.return_value = 1;
	}
	return (fd);
}
