/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:19:30 by enogawa           #+#    #+#             */
/*   Updated: 2022/12/14 03:52:16 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	sig_handler(int signal)
{
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signal;
}

void	minishell_signal(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		write (STDERR_FILENO, "signal_faild\n", 13);
		exit(EXIT_FAILURE);
	}
	return ;
}
