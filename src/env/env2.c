/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:14:04 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 14:10:48 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env **env_list)
{
	t_env	*tmp;

	if (!env_list || !*env_list)
		return ;
	while (*env_list)
	{
		tmp = (*env_list)->next;
		free((*env_list)->key);
		free((*env_list)->value);
		free(*env_list);
		*env_list = tmp;
	}
}

t_env	*env_new(char *key, char *value)
{
	t_env	*env_new;

	env_new = ft_calloc(1, sizeof(t_env));
	if (!env_new)
		assert_error("ft_calloc\n");
	env_new->key = key;
	env_new->value = value;
	return (env_new);
}

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
	env_new->pre = last;
	last->next = env_new;
	return ;
}
