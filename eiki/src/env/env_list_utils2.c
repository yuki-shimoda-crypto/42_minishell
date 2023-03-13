/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 02:06:26 by enogawa           #+#    #+#             */
/*   Updated: 2023/03/13 20:23:39 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*search_env(const char *key, t_env *env_list)
{
	if (!key || !env_list)
		return (NULL);
	while (env_list)
	{
		if (!strcmp(key, env_list->key))
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
		del_list->pre->next = del_list->next;
	if (del_list->next)
		del_list->next->prev = del_list->prev;
	free(del_list->key);
	del_list->key = NULL;
	free(del_list->value);
	del_list->value = NULL;
	free(del_list);
	del_list = NULL;
}
