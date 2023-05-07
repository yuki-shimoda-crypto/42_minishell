/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:05:49 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 14:13:51 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>

int	recognize_builtin(char **argv, t_env **env_list, bool one_cmd)
{
	if (!ft_strcmp("cd", argv[0]))
		g_return_error.return_value = builtin_cd(argv, env_list);
	else if (!ft_strcmp("echo", argv[0]))
		g_return_error.return_value = builtin_echo(argv);
	else if (!ft_strcmp("env", argv[0]))
		g_return_error.return_value = builtin_env(*env_list);
	else if (!ft_strcmp("exit", argv[0]))
		g_return_error.return_value = builtin_exit(argv, one_cmd);
	else if (!ft_strcmp("export", argv[0]))
		g_return_error.return_value = builtin_export(argv, env_list);
	else if (!ft_strcmp("pwd", argv[0]))
		g_return_error.return_value = builtin_pwd();
	else if (!ft_strcmp("unset", argv[0]))
		g_return_error.return_value = builtin_unset(argv, env_list);
	return (0);
}
