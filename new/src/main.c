/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:45:01 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/07 04:35:12 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

t_return_error	g_return_error;

void	free_token(t_tk **token)
{
	t_tk	*tmp;

	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->word);
		free(*token);
		*token = tmp;
	}
}

void	init_return_error(void)
{
	g_return_error.tokenize_error = false;
	g_return_error.parse_error = false;
	g_return_error.return_value = 0;
}

void	interpret(char *line)
{
	t_tk	*token;
//	t_node	*node;

	token = tokenize(line);
	if (g_return_error.tokenize_error)
		return ;
//	node = parse(token);
//	if (g_return_error.parse_error)
//		return ;
//	exec_cmd();
	print_t_tk(token);
	free_token(&token);
}

int	main(int argc, char const *argv[], char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		init_return_error();
		line = readline(PROMPT);
		if (!line)
		{
			write (STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (*line)
			add_history(line);
		interpret(line);
	}
}
