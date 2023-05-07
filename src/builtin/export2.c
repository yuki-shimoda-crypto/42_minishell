/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:59:41 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 15:57:32 by yshimoda         ###   ########.fr       */
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
			if (ft_strcmp(env_array[i], env_array[j]) > 0)
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

char	**put_env_into_array(t_env *env_list, char **sort_env)
{
	int	i;

	i = 0;
	while (env_list)
	{
		if (env_list->value[0] != '\0')
			sort_env[i] = ft_strjoin_three
				(env_list->key, "=\"", env_list->value);
		else
			sort_env[i] = ft_strdup(env_list->key);
		env_list = env_list->next;
		i++;
	}
	sort_env[i] = NULL;
	return (sort_env);
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
	return (put_env_into_array(env_list, sort_env));
}

bool	is_key_exist(const char *env, t_env *env_list)
{
	char	*key;
	char	*tail;

	if (!env || !env_list)
		return (false);
	tail = ft_strchr(env, '=');
	if (!tail)
		key = ft_strdup(env);
	else
		key = ft_strndup(env, tail - env);
	if (!key)
		assert_error("ft_strndup\n");
	while (env_list)
	{
		if (!ft_strcmp(key, env_list->key))
		{
			free(key);
			return (true);
		}
		env_list = env_list->next;
	}
	free(key);
	return (false);
}
