/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:39:29 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/14 20:25:44 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	print_env(t_env *env_list)
{
	while (env_list)
	{
		printf("%s=", env_list->key);
		printf("%s\n", env_list->value);
		env_list = env_list->next;
	}
	printf("_=/usr/bin/env\n");
}

int	env(char **argv, t_env *env_list)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		if (!strchr(argv[i], '='))
		{
			env_error(argv[i]);
			return (1);
		}
		i++;
	}
	print_env(env_list);
	if (argv[1])
	{
		i = 1;
		while (argv[i])
		{
			printf("%s\n", argv[i]);
			i++;
		}
	}
	return (0);
}
