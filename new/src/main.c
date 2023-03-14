/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:45:01 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/14 17:04:47 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

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
	g_return_error.return_value = 0;
	g_return_error.export_error = false;
}

void	interpret(char *line, t_env **env_list, char **envp)
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
	exec_cmd(node, env_list, envp);
	// print_t_tk(token);
	// print_node(node, 0);
	free_token(&token);
	free_node(&node);
}

//void	ctrl_c(int signal)
//{
//	rl_on_new_line();
//	write(STDOUT_FILENO, "\n", strlen("\n"));
//	rl_replace_line("", 0);
//	rl_redisplay();
//	rl_done = 1;
//	(void)signal;
//}
//int	func(void)
//{
//	printf("%s\n", "variable");
//	sleep(2);
//	return (0);
//}

void	ctrl_backslash(int sig)
{
	(void)sig;
	return ;
}

void	ctrl_c(int sig)
{
	g_return_error.g_sig = sig;
}

int	signal_hook(void)
{
	if (g_return_error.g_sig == 0)
		return (0);
	else if (g_return_error.g_sig == SIGINT)
	{
		g_return_error.g_sig = 0;
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}

void	setup_signal(void)
{
	rl_event_hook = signal_hook;
	rl_outstream = stderr;
	if (signal(SIGINT, ctrl_c) == SIG_ERR)
	{
		perror(NULL);
		assert_error("signal\n");
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror(NULL);
		assert_error("signal\n");
	}
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
			write (STDOUT_FILENO, "exit\n", strlen("exit\n"));
			break ;
		}
		if (*line)
		{
			add_history(line);
			interpret(line, &env_list, envp);
		}
		free(line);
	}
	free_env(&env_list);
}
