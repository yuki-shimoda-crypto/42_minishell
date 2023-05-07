/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:37:22 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 14:16:37 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(const char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp("cd", cmd))
		return (true);
	else if (!ft_strcmp("echo", cmd))
		return (true);
	else if (!ft_strcmp("env", cmd))
		return (true);
	else if (!ft_strcmp("exit", cmd))
		return (true);
	else if (!ft_strcmp("export", cmd))
		return (true);
	else if (!ft_strcmp("pwd", cmd))
		return (true);
	else if (!ft_strcmp("unset", cmd))
		return (true);
	else
		return (false);
}

void	exec_builtin(t_node *node, t_env **env_list, t_exec *exec_val)
{
	connect_pipe_builtin(node);
	recognize_builtin(exec_val->argv, env_list, exec_val->one_cmd);
	reset_pipe_builtin(node);
}
