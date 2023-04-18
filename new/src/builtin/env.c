/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:39:29 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/30 18:03:24 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	print_env(t_env *env_list)
{
	while (env_list)
	{
		write(STDOUT_FILENO, env_list->key, strlen(env_list->key));
		write(STDOUT_FILENO, "=", 1);
		if (env_list->value)
			write(STDOUT_FILENO, env_list->value, strlen(env_list->value));
		write(STDOUT_FILENO, "\n", 1);

		env_list = env_list->next;
	}
	write(STDOUT_FILENO, "_=/usr/bin/env\n", strlen("_=/usr/bin/env\n"));
}

int	builtin_env(t_env *env_list)
{
	print_env(env_list);
	return (0);
}
