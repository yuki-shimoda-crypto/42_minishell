/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:45:01 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/09 16:52:41 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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
}

void	init_return_error(void)
{
	g_return_error.tokenize_error = false;
	g_return_error.parse_error = false;
	g_return_error.exec_error = false;
	g_return_error.return_value = 0;
}

void	interpret(char *line, char **envp)
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
	exec_cmd(node, envp);
	// print_t_tk(token);
	// print_node(node, 0);
	free_token(&token);
	free_node(&node);
}

int	main(int argc, char const *argv[], char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	// (void)envp;
	while (1)
	{
		init_return_error();
		line = readline(PROMPT);
		if (!line)
		{
			write (STDOUT_FILENO, "exit\n", strlen("exit\n"));
			break ;
		}
		if (*line)
		{
			add_history(line);
			interpret(line, envp);
		}
		free(line);
	}
}
