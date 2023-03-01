/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogawa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:48:10 by enogawa           #+#    #+#             */
/*   Updated: 2023/01/13 21:49:38 by enogawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*env_last(t_env_list *env_list)
{
	if (!env_list)
		return (NULL);
	while (env_list->next)
		env_list = env_list->next;
	return (env_list);
}

void	env_addback(t_env_list **env_list, t_env_list *env_new)
{
	t_env_list	*last;

	if (!env_list || ! env_new)
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

void	free_env(t_env_list **env_box, int flag)
{
	t_env_list	*tmp;

	if (!env_box || !*env_box)
		return ;
	while (*env_box)
	{
		tmp = (*env_box)->next;
		free(*env_box);
		*env_box = tmp;
	}
	if (flag)
		exit(1);
}

t_env_list	*env_new(void)
{
	t_env_list	*env_new;

	env_new = ft_calloc(1, sizeof(t_env_list));
	if (!env_new)
		error_func("cannot allocate memory");
	return (env_new);
}
