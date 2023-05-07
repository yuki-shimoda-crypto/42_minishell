/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:40:09 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 19:40:38 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_pipe_num(t_node *node)
{
	size_t	num;

	num = 0;
	while (node)
	{
		node = node->pipe;
		num++;
	}
	return (num);
}
