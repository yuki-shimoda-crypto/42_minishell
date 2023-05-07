/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:39:30 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 19:39:58 by yshimoda         ###   ########.fr       */
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
