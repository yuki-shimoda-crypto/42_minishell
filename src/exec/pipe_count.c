/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:39:20 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 11:39:28 by yshimoda         ###   ########.fr       */
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
