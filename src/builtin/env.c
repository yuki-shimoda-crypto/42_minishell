/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:39:29 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 14:14:18 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	print_env(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->value[0] != '\0')
		{
			write(STDOUT_FILENO, env_list->key, ft_strlen(env_list->key));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, env_list->value, ft_strlen(env_list->value));
			write(STDOUT_FILENO, "\n", 1);
		}
		env_list = env_list->next;
	}
}

int	builtin_env(t_env *env_list)
{
	print_env(env_list);
	return (0);
}
