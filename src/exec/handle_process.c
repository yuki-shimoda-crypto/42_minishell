/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:37:47 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 11:39:03 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

bool	should_continue(t_node **node, t_exec *exec_val,
		bool is_continue, bool free_arg)
{
	if (is_continue)
	{
		if (free_arg)
			free_path_arg_node_next(node, exec_val);
		else
			free_path_node_next(node, exec_val);
		return (true);
	}
	else
		return (false);
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
	else
		exit(EXIT_FAILURE);
}

void	handle_parent_process(t_node *node, t_exec *exec_val)
{
	if (!node->pipe)
		exec_val->is_last_process = true;
	if (node->inpipe[0] != INT_MAX)
	{
		wrap_close(node->inpipe[1]);
		wrap_close(node->inpipe[0]);
	}
}
