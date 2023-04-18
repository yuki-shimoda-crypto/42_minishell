/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 04:23:38 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/16 12:01:47 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int	judge_nd_kind(char *redirect)
{
	if (!strncmp(redirect, ">>", 2))
		return (ND_REDIRECT_APPEND);
	else if (!strncmp(redirect, "<<", 2))
		return (ND_REDIRECT_HEREDOC);
	else if (!strncmp(redirect, ">", 1))
		return (ND_REDIRECT_OUT);
	else if (!strncmp(redirect, "<", 1))
		return (ND_REDIRECT_IN);
	return (0);
}

t_tk	*dup_token(char *word)
{
	t_tk	*token;

	token = calloc(1, sizeof(t_tk));
	if (!token)
		assert_error("calloc");
	token->word = strdup(word);
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
