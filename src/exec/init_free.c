/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:37:59 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 11:38:06 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	init_exec_val(t_exec *exec_val)
{
	exec_val->pathname = NULL;
	exec_val->argv = NULL;
	exec_val->envp = NULL;
	exec_val->pid = 0;
	exec_val->is_last_process = false;
	exec_val->one_cmd = false;
}

void	free_path_node_next(t_node **node, t_exec *exec_val)
{
	free(exec_val->pathname);
	*node = (*node)->pipe;
	g_return_error.error = false;
}

void	free_path_arg_node_next(t_node **node, t_exec *exec_val)
{
	free_argv(exec_val->argv);
	free_path_node_next(node, exec_val);
}
