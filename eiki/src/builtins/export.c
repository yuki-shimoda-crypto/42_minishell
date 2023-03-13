/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:30:21 by enogawa           #+#    #+#             */
/*   Updated: 2023/03/14 02:53:07 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_env	t_env;
struct s_env
{
	char		*key;
	char		*value;
	t_env		*pre;
	t_env		*next;
};

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

static char	**sort_array(char **env_array)
{
	char	*temp;
	size_t	i;

	i = 0;
	while (env_array[i])
	{
		if (strcmp(env_array[i], env_array[i + 1]) < 0)
		{
			temp = env_array[i];
			free(env_array[i]);
			env_array[i] = env_array[i + 1];
			free(env_array[i + 1]);
			env_array[i + 1] = temp;
			free(temp);
		}
		i++;
	}
	return (env_array);
}

static char	**env_into_array(t_env *env_list)
{
	char	**sort_env;
	char	*temp;
	size_t	i;

	sort_env = malloc(sizeof(char *) * i + 1);
	if (!sort_env)
		assert_error("malloc");
	i = 0;
	while (env_list)
	{
		temp = strdup(env_list->key);
		if (!temp)
			assert_error("stdup");
		sort_env[i] = strjointhree(temp, "=", env_list->value);
		free(temp);
		env_list = env_list->next;
		i++;
	}
	sort_env[i] = NULL;
}

static void	put_sorted_env(t_env *env_list)
{
	size_t	i;
	t_env	*tmp;
	char	**sort_env;

	if (!env_list)
		return ;
	tmp = env_list;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	sort_env = env_into_array(env_list);
	sort_env = sort_array(sort_env);
	i = 0;
	while (sort_env[i])
	{
		write (1, "declare -x ", strlen("declare -x "));
		write (1, sort_env[i], strlen(sort_env[i]));
		write (1, "\n", 1);
		i++;
	}
}

int	export(char **argv, t_env **env_list)
{
	t_env	*new;
	t_env	*cmp;
	size_t	num;

	num = 0;
	while (add_env[num])
		num++;
	if (num == 1)
		put_sorted_env(env_list);
	else
	{
		new = env_new();
		env_add(add_env, env_list);
	}
}

int main(void)
{
	return (0);
}
