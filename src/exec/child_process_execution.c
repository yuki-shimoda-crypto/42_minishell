/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:46:03 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/08 01:25:39 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	process_node(t_node **node, t_env **env_list, t_exec *exec_val)
{
	redirect_fd_list((*node)->redirect, *env_list);
	if (g_return_error.error)
	{
		*node = (*node)->pipe;
		return ;
	}
	exec_val->pathname = make_pathname((*node)->token, *env_list);
	if (g_return_error.error)
	{
		free_path_node_next(node, exec_val);
		return ;
	}
	exec_val->argv = make_argv((*node)->token);
	if (!exec_val->argv)
	{
		free_path_node_next(node, exec_val);
		return ;
	}
	do_redirect((*node)->redirect);
	if ((*node)->token->kind != TK_WORD)
	{
		reset_redirect((*node)->redirect);
		free_path_arg_node_next(node, exec_val);
		return ;
	}
}

void	exec_child_process(t_node *node, t_env **env_list, t_exec *exec_val)
{
	exec_val->pid = fork();
	if (exec_val->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (exec_val->pid == 0)
		handle_child_process(node, env_list, exec_val);
	else
		handle_parent_process(node, exec_val);
}
