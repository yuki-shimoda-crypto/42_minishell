/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:20:11 by yshimoda          #+#    #+#             */
/*   Updated: 2022/12/18 19:09:03 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_lst	*cmd_last(t_cmd_lst *cmd_lst)
{
	if (!cmd_lst)
		return (NULL);
	while (cmd_lst->next)
		cmd_lst = cmd_lst->next;
	return (cmd_lst);
}

void	cmd_addfront(t_cmd_lst **cmd_lst, t_cmd_lst *cmd_new)
{
	if (!cmd_lst || !cmd_new)
		return ;
	cmd_new->next = *cmd_lst;
	if (*cmd_lst)
		(*cmd_lst)->pre = cmd_new;
	*cmd_lst = cmd_new;
	return ;
}

void	cmd_addback(t_cmd_lst **cmd_lst, t_cmd_lst *cmd_new)
{
	t_cmd_lst	*last;

	if (!cmd_lst || ! cmd_new)
		return ;
	if (!*cmd_lst)
	{
		*cmd_lst = cmd_new;
		return ;
	}
	last = cmd_last(*cmd_lst);
	cmd_new->pre = last;
	last->next = cmd_new;
	return ;
}

size_t	cmd_size(t_cmd_lst *cmd_lst)
{
	size_t	i;

	i = 0;
	while (cmd_lst)
	{
		cmd_lst = cmd_lst->next;
		i++;
	}
	return (i);
}

t_cmd_lst	*cmd_new(const char *cmd)
{
	t_cmd_lst	*cmd_new;

	cmd_new = ft_calloc(1, sizeof(t_cmd_lst));
	if (!cmd_new)
		error_func("malloc error");
	cmd_new->cmd = cmd;
	return (cmd_new);
}
