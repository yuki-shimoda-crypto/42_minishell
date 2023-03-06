/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:04:47 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/07 02:34:56 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

const char	*print_t_tk_kind(int kind)
{
	if (kind == TK_WORD)
		return ("TK_WORD");
	if (kind == TK_REDIRECT)
		return ("TK_REDIRECT");
	if (kind == TK_PIPE)
		return ("TK_PIPE");
	if (kind == TK_EOF)
		return ("TK_EOF");
	return (NULL);
}

void	print_t_tk(t_tk	*token)
{
	if (token)
		printf("%s\n", "----------");
	while (token)
	{
		printf("%s\n", token->word);
		printf("\t%s\n", print_t_tk_kind(token->kind));
		printf("%s\n", "----------");
		token = token->next;
	}
}
