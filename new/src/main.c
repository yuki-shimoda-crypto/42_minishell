/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:45:01 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/04 19:47:332 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

t_return_error	g_return_error;

void	interpret(const char *line)
{
	t_tk	*token;

	token = NULL;
	tokenize(&token, line);
	if (g_return_error)
		return ;
}

int	main(int argc, char const *argv[], char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		g_return_error.tokenize_error = false;
		g_return_error.parse_error = false;
		g_return_error.reurn_value = false;
		line = readline("minishell#");
		if (!line)
		{
			write (STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (*line)
			add_history(line);
		printf("%s\n", line);
		interpret(line);
	}
}
