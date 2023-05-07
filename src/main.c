/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:45:01 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 14:14:18 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

t_return_error	g_return_error;

void	init_return_error(void)
{
	g_return_error.tokenize_error = false;
	g_return_error.parse_error = false;
	g_return_error.error = false;
	g_return_error.export_error = false;
	g_return_error.heredoc_interupt = false;
}

void	interpret(char *line, t_env **env_list)
{
	t_tk	*token;
	t_node	*node;

	token = tokenize(line);
	if (g_return_error.tokenize_error)
	{
		free_token(&token);
		return ;
	}
	node = parse(token);
	if (g_return_error.parse_error)
		return ;
	exec_cmd(node, env_list);
	free_token(&token);
	free_node(&node);
}

int	into_minishell(char *line, t_env *env_list)
{
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			wrap_write (STDOUT_FILENO, "exit\n", ft_strlen("exit\n"));
		return (1);
	}
	if (*line)
	{
		add_history(line);
		interpret(line, &env_list);
	}
	free(line);
	return (0);
}

int	main(int argc, char const *argv[], char *envp[])
{
	char	*line;
	t_env	*env_list;

	(void)argc;
	(void)argv;
	setup_signal();
	rl_outstream = stderr;
	env_list = make_env_list(envp);
	while (1)
	{
		init_return_error();
		line = readline(PROMPT);
		if (into_minishell(line, env_list))
			break ;
	}
	free_env(&env_list);
	return (g_return_error.return_value);
}
