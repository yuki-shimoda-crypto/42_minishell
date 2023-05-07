/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:44:11 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 19:47:21 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	free_path_node_next(t_node **node, t_exec *exec_val)
{
	free(exec_val->pathname);
	*node = (*node)->pipe;
	g_return_error.error = true;
}

void	free_path_arg_node_next(t_node **node, t_exec *exec_val)
{
	free_argv(exec_val->argv);
	free_path_node_next(node, exec_val);
}

void	input_pipe_and_expand(t_node *node, t_env **env_list, t_exec *exec_val)
{
	input_pipefd(node, NULL);
	expand(node, *env_list);
	init_exec_val(exec_val);
	exec_val->envp = make_envp(*env_list);
}
