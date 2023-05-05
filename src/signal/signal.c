/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:29:02 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/05 13:34:51 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

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
		g_return_error.ctrl_c = true;
		g_return_error.heredoc_interupt = true;
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}

void	setup_signal(void)
{
	if (isatty(STDIN_FILENO))
		rl_event_hook = signal_hook;
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
