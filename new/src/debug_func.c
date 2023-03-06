/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:04:47 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/06 15:07:09 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_t_tk(t_tk	*token)
{
	while (*token)
	{
		printf("%s\n", token->word);
		printf("%d\n", token->kind);
		token = token->next;
	}
}

