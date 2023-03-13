/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 02:36:44 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/14 03:34:58 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	free_array(char **env_array)
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

static void	sort_array(char **env_array)
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
			if (strcmp(env_array[i], env_array[j]) < 0)
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

static char	**env_into_array(t_env *env_list)
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
		sort_env[i] = strjoin_three(env_list->key, "=", env_list->value);
		env_list = env_list->next;
		i++;
	}
	sort_env[i] = NULL;
	return (sort_env);
}

static void	put_sorted_env(t_env *env_list)
{
	char	**sort_env;
	size_t	i;

	if (!env_list)
		return ;
	sort_env = env_into_array(env_list);
	sort_array(sort_env);
	i = 0;
	while (sort_env[i])
	{
		write (1, "declare -x ", strlen("declare -x "));
		write (1, sort_env[i], strlen(sort_env[i]));
		write (1, "\n", 1);
		i++;
	}
	free_array(sort_env);
}

int	builtin_export(char **argv, t_env **env_list)
{
	size_t	num;
	size_t	i;

	if (!argv || !*argv || !env_list)
		return (1);
	num = 0;
	while (argv[num])
		num++;
	if (num == 1)
		put_sorted_env(*env_list);
	else
	{
		i = 0;
		while (argv[i])
		{
			add_env(argv[i], env_list);
			i++;
		}
	}
	return (0);
}
