/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:59:41 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/06 15:42:05 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **env_array)
{
	size_t	i;

	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

void	sort_array(char **env_array)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	while (env_array[i])
	{
		j = i + 1;
		while (env_array[j])
		{
			if (strcmp(env_array[i], env_array[j]) > 0)
			{
				temp = env_array[i];
				env_array[i] = env_array[j];
				env_array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

char	**env_into_array(t_env *env_list)
{
	t_env	*tmp;
	char	**sort_env;
	size_t	i;

	i = 0;
	tmp = env_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	sort_env = malloc(sizeof(char *) * (i + 1));
	if (!sort_env)
		assert_error("malloc\n");
	i = 0;
	while (env_list)
	{
		if (env_list->value[0] != '\0')
			sort_env[i] = strjoin_three(env_list->key, "=\"", env_list->value);
		else
			sort_env[i] = strdup(env_list->key);
		env_list = env_list->next;
		i++;
	}
	sort_env[i] = NULL;
	return (sort_env);
}

bool	is_key_exist(const char *env, t_env *env_list)
{
	char	*key;
	char	*tail;

	if (!env || !env_list)
		return (false);
	tail = strchr(env, '=');
	if (!tail)
		key = strdup(env);
	else
		key = strndup(env, tail - env);
	if (!key)
		assert_error("strndup\n");
	while (env_list)
	{
		if (!strcmp(key, env_list->key))
		{
			free(key);
			return (true);
		}
		env_list = env_list->next;
	}
	free(key);
	return (false);
}
