/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:41:30 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 14:15:30 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

t_env	*search_env(const char *key, t_env *env_list)
{
	if (!key || !env_list)
		return (NULL);
	while (env_list)
	{
		if (!ft_strcmp(key, env_list->key))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	del_env(const char *key, t_env **env_list)
{
	t_env	*del_list;

	if (!key || !env_list)
		return ;
	del_list = search_env(key, *env_list);
	if (!del_list)
		return ;
	if (del_list == *env_list)
		*env_list = (*env_list)->next;
	if (del_list->pre)
		(del_list->pre)->next = del_list->next;
	if (del_list->next)
		(del_list->next)->pre = del_list->pre;
	free(del_list->key);
	free(del_list->value);
	free(del_list);
}

void	creat_and_add(char *key, char *value, t_env **env_list)
{
	t_env	*new_env_list;

	new_env_list = env_new(key, value);
	if (!new_env_list)
		assert_error("env_new\n");
	env_addback(env_list, new_env_list);
}

void	add_env(const char *env, t_env **env_list)
{
	char		*tail;
	char		*key;
	char		*value;

	if (!env || !env_list)
		return ;
	tail = ft_strchr(env, '=');
	if (!tail)
	{
		key = ft_strdup(env);
		value = ft_calloc(1, 1);
	}
	else
	{
		key = ft_strndup(env, tail - env);
		if (!key)
			assert_error("ft_strndup\n");
		tail++;
		value = ft_strdup(tail);
		if (!value)
			assert_error("ft_strdup\n");
	}
	return (creat_and_add(key, value, env_list));
}

t_env	*make_env_list(char **envp)
{
	t_env	*env_list;
	size_t	i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		add_env(envp[i], &env_list);
		i++;
	}
	return (env_list);
}
