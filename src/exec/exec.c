/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 04:15:24 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 19:47:07 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>

void	exec(char *pathname, char **argv, char **envp, t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		assert_error("fork\n");
	else if (pid == 0)
	{
		connect_pipe(node);
		execve(pathname, argv, envp);
		assert_error("execve\n");
	}
}

void	init_exec_val(t_exec *exec_val)
{
	exec_val->pathname = NULL;
	exec_val->argv = NULL;
	exec_val->envp = NULL;
	exec_val->pid = 0;
	exec_val->one_cmd = false;
	exec_val->is_overwrite = false;
}

void	exec_cmd(t_node *node, t_env **env_list)
{
	t_exec	exec_val;

	input_pipe_and_expand(node, env_list, &exec_val);
	if (!node->pipe)
		exec_val.one_cmd = true;
	while (node)
	{
		process_node(&node, env_list, &exec_val);
		if (g_return_error.error)
		{
			g_return_error.error = false;
			continue ;
		}
		if (exec_val.argv && is_builtin(exec_val.argv[0]) && exec_val.one_cmd)
			handle_builtin(node, env_list, &exec_val);
		else
			exec_child_process(node, env_list, &exec_val);
		reset_redirect(node->redirect);
		node = node->pipe;
		free(exec_val.pathname);
		free_argv(exec_val.argv);
	}
	free_envp(exec_val.envp);
	wait_child_process(&exec_val);
}
