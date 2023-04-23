/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:45:01 by enogaWa           #+#    #+#             */
/*   Updated: 2023/04/06 15:34:31 by enogaWa          ###   ########.fr       */
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

void	free_token(t_tk **token)
{
	t_tk	*tmp;

	if (!token)
		return ;
	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->word);
		free(*token);
		*token = tmp;
	}
}

void	free_node(t_node **node)
{
	if (!node)
		return ;
	if ((*node)->redirect)
		free_node(&(*node)->redirect);
	if ((*node)->pipe)
		free_node(&(*node)->pipe);
	if ((*node)->token)
		free_token(&(*node)->token);
	free((*node)->filename);
	free(*node);
}

void	init_return_error(void)
{
	g_return_error.tokenize_error = false;
	g_return_error.parse_error = false;
	g_return_error.redirect_error = false;
	g_return_error.exec_error = false;
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
	// print_node(node, 0);
	free_token(&token);
	free_node(&node);
}

int	main(int argc, char const *argv[], char *envp[])
{
	char	*line;
	t_env	*env_list;

	(void)argc;
	(void)argv;
	setup_signal();
	env_list = make_env_list(envp);
	while (1)
	{
		init_return_error();
		line = readline(PROMPT);
		if (!line)
		{
//			wrap_write (STDOUT_FILENO, "exit", strlen("exit\n"));
//			if (g_return_error.ctrl_c == false)
//				wrap_write(STDOUT_FILENO, "\n", 1);
			break ;
		}
		if (*line)
		{
			add_history(line);
			interpret(line, &env_list);
		}
		free(line);
	}
	free_env(&env_list);
}
