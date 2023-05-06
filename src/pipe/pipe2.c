/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:32:08 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/06 20:36:53 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect_in_exist(t_node *node)
{
	while (node)
	{
		if (node->kind == ND_REDIRECT_IN || node->kind == ND_REDIRECT_HEREDOC)
			return (true);
		node = node->redirect;
	}
	return (false);
}

bool	is_redirect_out_exist(t_node *node)
{
	while (node)
	{
		if (node->kind == ND_REDIRECT_OUT || node->kind == ND_REDIRECT_APPEND)
			return (true);
		node = node->redirect;
	}
	return (false);
}
