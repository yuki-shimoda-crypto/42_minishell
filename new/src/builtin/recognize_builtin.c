/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:05:49 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/14 03:56:18 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	recognize_builtin(char **argv, t_env **env_list)
{
	// if (!strncmp("cd", argv[0], 2))
	// 	cd(argv);
	if (!strncmp("echo", argv[0], 4))
		builtin_echo(argv);
	// else if (!strncmp("env", argv[0], 3))
	// 	env(argv);
	// else if (!strncmp("exit", argv[0], 4))
	// 	exit(argv);
	else if (!strncmp("export", argv[0], 6))
		builtin_export(argv, env_list);
	// else if (!strncmp("pwd", argv[0], 3))
	// 	pwd(argv);
	// else if (!strncmp("unset", argv[0], 5))
	// 	unset(argv);
}
