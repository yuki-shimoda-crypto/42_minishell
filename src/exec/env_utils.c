/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:37:35 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 11:37:39 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

size_t	env_list_size(t_env *env_list)
{
	size_t		i;

	i = 0;
	while (env_list)
	{
		env_list = env_list->next;
		i++;
	}
	return (i);
}

char	**make_envp(t_env *env_list)
{
	char	**envp;
	size_t	list_size;
	size_t	i;

	list_size = env_list_size(env_list);
	envp = calloc(list_size + 1, sizeof(char *));
	if (!envp)
		assert_error("calloc\n");
	i = 0;
	while (i < list_size)
	{
		envp[i] = strjoin_three(env_list->key, "=", env_list->value);
		if (!envp[i])
			assert_error("strjoin_three, malloc\n");
		i++;
		env_list = env_list->next;
	}
	return (envp);
}

void	free_envp(char **envp)
{
	size_t	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}
