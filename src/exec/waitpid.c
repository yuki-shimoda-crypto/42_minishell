/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:39:15 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 11:39:16 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void	handle_waitpid_error(pid_t pid)
{
	if (pid == -1)
	{
		perror(NULL);
		assert_error("waitpid\n");
	}
}

void	update_return_value(pid_t pid, int status, t_exec *exec_val)
{
	if (WIFEXITED(status) && pid == exec_val->pid && exec_val->is_last_process)
		g_return_error.return_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (isatty(STDIN_FILENO))
			wrap_write(STDOUT_FILENO, "\n", 1);
		g_return_error.g_sig = 0;
		if (WTERMSIG(status) == SIGINT)
			g_return_error.ctrl_c = true;
		g_return_error.return_value = 128 + WTERMSIG(status);
	}
}

void	wait_child_process(t_exec *exec_val)
{
	int		status;
	pid_t	pid;

	status = 0;
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1 && errno == ECHILD)
			break ;
		else
		{
			handle_waitpid_error(pid);
			update_return_value(pid, status, exec_val);
		}
	}
}
