/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogawa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 02:06:26 by enogawa           #+#    #+#             */
/*   Updated: 2023/01/14 02:43:49 by enogawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*search_env(char *key_name, t_env_list *env_box)
{
	t_env_list	*tmp;
	size_t		len;

	tmp = env_box;
	len = ft_strlen(key_name);
	while (tmp)
	{
		if (!ft_strncmp(key_name, tmp->key, len + 1))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	del_env(char *key_name, t_env_list *env_box)
{
	t_env_list	*del_target;

	del_target = search_env(key_name, env_box);
	if (!del_target)
		return ;
	del_target->prev->next = del_target->next;
	del_target->next->prev = del_target->prev;
	free(del_target->key);
	del_target->key = NULL;
	free(del_target->value);
	del_target->value = NULL;
	free(del_target);
	del_target = NULL;
}
