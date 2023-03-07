/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:52:17 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/07 16:46:41 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

// ok_yshimoda
t_tk	*token_new(char *word, t_tk_kind kind)
{
	t_tk	*token;

	token = calloc(1, sizeof(t_tk));
	if (!token)
		assert_error("calloc\n");
	token->word = word;
	token->kind = kind;
	token->next = NULL;
	return (token);
}

// ok
static void	skip_blank(char **skipped, char *line)
{
	while (is_blank(*line))
		line++;
	*skipped = line;
}

t_tk	*tokenize(char *line)
{
	t_tk	head;
	t_tk	*token;

	token = &head;
	token->word = NULL;
	token->kind = TK_WORD;
	token->next = NULL;
	while (*line)
	{
		if (is_blank(*line))
			skip_blank(&line, line);
		else if (is_quoted(*line, &line, line))
		{
			token->next = quoted_into_list(&line, line, *line);
			token = token->next;
		}
		else if (is_redirect(*line, &line, line))
		{
			token->next = redirect_into_list(&line, line, *line, token);
			token = token->next;
		}
		else if (is_pipe(*line))
		{
			token->next = pipe_into_list(&line, line, token);
			token = token->next;
		}
		else
		{
			token->next = word_into_list(&line, line);
			token = token->next;
		}
	}
	if (!g_return_error.tokenize_error)
	{
		if (token && token->kind == TK_REDIRECT)
		{
			syntax_error("< or >\n", &line, line);
			g_return_error.tokenize_error = true;
		}
		else if (token && token->kind == TK_PIPE)
		{
			syntax_error("|\n", &line, line);
			g_return_error.tokenize_error = true;
		}
	}
	token->next = token_new(NULL, TK_EOF);
	return (head.next);
}
