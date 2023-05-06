/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:22:42 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/06 16:39:46 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_tk **token)
{
	t_tk	*tmp;

	if (!token)
		return ;
	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->word);
		free(*token);
		*token = tmp;
	}
}

void	free_node(t_node **node)
{
	if (!node)
		return ;
	if ((*node)->redirect)
		free_node(&(*node)->redirect);
	if ((*node)->pipe)
		free_node(&(*node)->pipe);
	if ((*node)->token)
		free_token(&(*node)->token);
	free((*node)->filename);
	free(*node);
}
