/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 04:23:38 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 14:15:18 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int	judge_nd_kind(char *redirect)
{
	if (!ft_strncmp(redirect, ">>", 2))
		return (ND_REDIRECT_APPEND);
	else if (!ft_strncmp(redirect, "<<", 2))
		return (ND_REDIRECT_HEREDOC);
	else if (!ft_strncmp(redirect, ">", 1))
		return (ND_REDIRECT_OUT);
	else if (!ft_strncmp(redirect, "<", 1))
		return (ND_REDIRECT_IN);
	return (0);
}

t_tk	*dup_token(char *word)
{
	t_tk	*token;

	token = ft_calloc(1, sizeof(t_tk));
	if (!token)
		assert_error("ft_calloc");
	token->word = ft_strdup(word);
	token->kind = TK_WORD;
	return (token);
}

t_tk	*dup_simple_command_token(t_tk **skipped, t_tk *token)
{
	t_tk	head;
	t_tk	*new_token;

	new_token = &head;
	new_token->word = NULL;
	new_token->kind = TK_WORD;
	new_token->next = NULL;
	while (token->kind != TK_EOF && token->kind != TK_PIPE)
	{
		if (token->kind == TK_REDIRECT)
			token = token->next->next;
		else
		{
			new_token->next = dup_token(token->word);
			new_token = new_token->next;
			token = token->next;
		}
	}
	new_token->next = token_new(NULL, TK_EOF);
	*skipped = token;
	return (head.next);
}
