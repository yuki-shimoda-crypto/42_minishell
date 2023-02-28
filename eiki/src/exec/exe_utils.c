/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:00:33 by enogaWa           #+#    #+#             */
/*   Updated: 2023/02/28 15:35:42 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	tk_num(t_token_list	*token)
{
	size_t	len;

	len = 0;
	while (token->kind != TK_EOF)
	{
		if (token->kind == TK_WORD)
			len++;
		token = token->next;
	}
	return (len);
}

static char	**put_array(char	**exe_array, t_token_list	*tk_list)
{
	size_t	i;

	i = 0;
	while (tk_list->kind != TK_EOF)
	{
		if (tk_list->kind == TK_WORD)
		{
			exe_array[i] = tk_list->token;
			i++;
		}
		tk_list = tk_list->next;
	}
	exe_array[i] = NULL;
	return (exe_array);
}

char	**make_array(t_token_list	*tk_list)
{
	char	**exe_array;
	size_t	len;

	len = tk_num(tk_list);
	exe_array = ft_calloc(sizeof(char **), len + 1);
	// if (!exe_array)
	// 	error(malloc);
	return (put_array(exe_array, tk_list));
}
