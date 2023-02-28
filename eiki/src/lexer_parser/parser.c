/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:12:06 by enogawa           #+#    #+#             */
/*   Updated: 2023/02/28 22:56:14 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	count_quote(char *token)
// {
// 	size_t	i;
// 	size_t	count;

// 	i = 0;
// 	count = 0;
// 	while (token[i] != '\0')
// 	{
// 		if (token[i] == '\'' || token[i] == '"')
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// static void	remove_quote(t_token_list	*tk_list)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	count;
// 	char	*tmp;

// 	i = 0;
// 	j = 0;
// 	count = count_quote(tk_list->token);
// 	tmp = malloc(sizeof(char) * ft_strlen(tk_list->token) - count);
// 	while (tk_list->token[i] != '\0')
// 	{
// 		while (tk_list->token[i] == '\'' || tk_list->token[i] == '"')
// 			i++;
// 		tmp[j] = tk_list->token[i];
// 		j++;
// 		i++;
// 	}
// 	tk_list->token = tmp;
// }

// static void	quote_remove_cmd(t_token_list	*tk_list)
// {
// 	remove_quote(tk_list);
// 	tk_list = tk_list->next;
// 	while (tk_list->kind != TK_EOF)
// 	{
// 		if (tk_list->kind == TK_PIPE && tk_list->next->kind == TK_WORD)
// 		{
// 			tk_list = tk_list->next;
// 			remove_quote(tk_list);
// 		}
// 		tk_list = tk_list->next;
// 	}
// }

static void	interpret(t_token_list	*tk_list)
{
	t_token_list	*tmp;

	tmp = tk_list;
	while (tmp->kind != TK_EOF)
	{
		if (tmp->kind == TK_OP)
		{
			redirection(tk_list);
			break ;
		}
		tmp = tmp->next;
	}
}

int	parser(t_token_list	*tk_list)
{
	t_token_list	*tmp;

	tmp = tk_list;
	// quote_remove_cmd(tk_list);
	interpret(tmp);
	return (0);
}
