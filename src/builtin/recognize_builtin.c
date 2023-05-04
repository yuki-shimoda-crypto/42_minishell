/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:05:49 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/30 18:02:26 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>

int	recognize_builtin(char **argv, t_env **env_list)
{
	if (!strcmp("cd", argv[0]))
		g_return_error.return_value = builtin_cd(argv, env_list);
	else if (!strcmp("echo", argv[0]))
		g_return_error.return_value = builtin_echo(argv);
	else if (!strcmp("env", argv[0]))
		builtin_env(*env_list);
	else if (!strcmp("exit", argv[0]))
		builtin_exit(argv);
	else if (!strcmp("export", argv[0]))
		builtin_export(argv, env_list);
	else if (!strcmp("pwd", argv[0]))
		builtin_pwd();
	else if (!strcmp("unset", argv[0]))
		builtin_unset(argv, env_list);
	return (0);
}
