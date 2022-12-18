/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:20:11 by yshimoda          #+#    #+#             */
/*   Updated: 2022/12/18 19:09:19 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_del_front(t_cmd_lst **cmd_lst)
{
	t_cmd_lst	*tmp;

	if (!cmd_lst || !*cmd_lst)
		return ;
	tmp = (*cmd_lst)->next;
	free(*cmd_lst);
	*cmd_lst = tmp;
	if (!*cmd_lst)
		return ;
	(*cmd_lst)->pre = NULL;
	if ((*cmd_lst)->next)
		(*cmd_lst)->next->pre = *cmd_lst;
	return ;
}

void	cmd_clear(t_cmd_lst **cmd_lst)
{
	t_cmd_lst	*tmp;

	if (!cmd_lst || !*cmd_lst)
		return ;
	while (*cmd_lst)
	{
		tmp = (*cmd_lst)->next;
		free(*cmd_lst);
		*cmd_lst = tmp;
	}
	return ;
}
