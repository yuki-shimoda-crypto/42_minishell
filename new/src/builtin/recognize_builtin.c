/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:05:49 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/13 18:41:03 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	recognize_builtin(char **argv)
{
	// if (!strncmp("cd", argv[0], 2))
	// 	cd(argv);
	if (!strncmp("echo", argv[0], 4))
		echo(argv);
	// else if (!strncmp("env", argv[0], 3))
	// 	env(argv);
	// else if (!strncmp("exit", argv[0], 4))
	// 	exit(argv);
	// else if (!strncmp("export", argv[0], 6))
	// 	export(argv);
	// else if (!strncmp("pwd", argv[0], 3))
	// 	pwd(argv);
	// else if (!strncmp("unset", argv[0], 5))
	// 	unset(argv);
}