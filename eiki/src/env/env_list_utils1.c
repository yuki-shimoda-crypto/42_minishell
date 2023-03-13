/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:48:10 by enogawa           #+#    #+#             */
/*   Updated: 2023/03/13 19:50:23 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_last(t_env *env_list)
{
	if (!env_list)
		return (NULL);
	while (env_list->next)
		env_list = env_list->next;
	return (env_list);
}

void	env_addback(t_env **env_list, t_env *env_new)
{
	t_env	*last;

	if (!env_list || !env_new)
		return ;
	if (!*env_list)
	{
		*env_list = env_new;
		return ;
	}
	last = env_last(*env_list);
	env_new->prev = last;
	last->next = env_new;
	return ;
}

void	free_env(t_env **env_list)
{
	t_env	*tmp;

	if (!env_list || !*env_list)
		return ;
	while (*env_list)
	{
		tmp = (*env_list)->next;
		free(*env_list);
		*env_list = tmp;
	}
}

t_env	*env_new(char *key, char *value)
{
	t_env	*env_new;

	env_new = calloc(1, sizeof(t_env));
	if (!env_new)
		assert_error("calloc\n");
	env_new->key = key;
	env_new->value = value;
	return (env_new);
}
