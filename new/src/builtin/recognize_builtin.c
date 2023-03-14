/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:05:49 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/14 17:10:22 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>

void	recognize_builtin(char **argv, t_env **env_list)
{
	
	// if (!strcmp("cd", argv[0]))
	// 	cd(argv);
	if (!strcmp("echo", argv[0]))
		builtin_echo(argv);
	// else if (!strcmp("env", argv[0]))
	// 	env(argv);
	// else if (!strcmp("exit", argv[0]))
	// 	exit(argv);
	// else if (!strcmp("export", argv[0]))
	else if (!strcmp("export", argv[0]))
		builtin_export(argv, env_list);
	// else if (!strcmp("pwd", argv[0]))
	// 	pwd(argv);
	// else if (!strcmp("unset", argv[0]))
	// 	unset(argv);
}
