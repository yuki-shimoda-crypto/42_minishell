/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:54:58 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/06 20:37:48 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

static void	expand_and_put(bool flag, char *input, t_env *env_list, int fd)
{
	char	*expanded;

	if (!flag)
		expanded = expand_word(input, ND_SIMPLE_CMD, env_list);
	else
		expanded = input;
	write(fd, expanded, strlen(expanded));
	write(fd, "\n", strlen("\n"));
	free(expanded);
}

int	heredoc(char *delimiter, t_env *env_list, bool quote_flag)
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
		expand_and_put(quote_flag, input, env_list, pipe_fd[1]);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
