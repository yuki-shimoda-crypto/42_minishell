/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:54:58 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/26 16:12:22 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int	heredoc(char *delimiter)
{
	char	*input;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		assert_error("pipe\n");
	g_return_error.heredoc_interupt = false;
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		if (g_return_error.heredoc_interupt || !strcmp(input, delimiter))
		{
			free(input);
			break ;
		}
		write (pipe_fd[1], input, strlen(input));
		write (pipe_fd[1], "\n", strlen("\n"));
		free(input);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
