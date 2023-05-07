/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:44:58 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 20:25:43 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	handle_builtin(t_node *node, t_env **env_list, t_exec *exec_val)
{
	connect_pipe_builtin(node);
	recognize_builtin(exec_val->argv, env_list, exec_val->one_cmd);
	reset_pipe_builtin(node);
}

void	handle_child_process(t_node *node, t_env **env_list, t_exec *exec_val)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	connect_pipe(node);
	if (exec_val->argv && is_builtin(exec_val->argv[0]))
		exit(recognize_builtin(exec_val->argv, env_list, exec_val->one_cmd));
	else if (exec_val->pathname && exec_val->argv)
	{
		execve(exec_val->pathname, exec_val->argv, exec_val->envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	handle_parent_process(t_node *node, t_exec *exec_val)
{
	if (!node->pipe)
		exec_val->is_overwrite = true;
	if (node->inpipe[0] != INT_MAX)
	{
		wrap_close(node->inpipe[1]);
		wrap_close(node->inpipe[0]);
	}
}
