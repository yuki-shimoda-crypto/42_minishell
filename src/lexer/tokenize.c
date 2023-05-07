/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:52:17 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 14:10:48 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

t_tk	*token_new(char *word, t_tk_kind kind)
{
	t_tk	*token;

	token = ft_calloc(1, sizeof(t_tk));
	if (!token)
		assert_error("ft_calloc\n");
	token->word = word;
	token->kind = kind;
	token->next = NULL;
	return (token);
}

static void	skip_blank(char **skipped, char *line)
{
	while (is_blank(*line))
		line++;
	*skipped = line;
}

static void	judge_kind_and_put(t_tk **token, char *line)
{
	while (*line)
	{
		if (is_blank(*line))
			skip_blank(&line, line);
		else if (is_quoted(*line, &line, line))
		{
			(*token)->next = quoted_into_list(&line, line, *line);
			(*token) = (*token)->next;
		}
		else if (is_redirect(*line, &line, line))
		{
			(*token)->next = redirect_into_list(&line, line, *line, *token);
			(*token) = (*token)->next;
		}
		else if (is_pipe(*line))
		{
			(*token)->next = pipe_into_list(&line, line, *token);
			(*token) = (*token)->next;
		}
		else
		{
			(*token)->next = word_into_list(&line, line);
			(*token) = (*token)->next;
		}
	}
}

static void	error_token(t_tk *token, t_tk head, char *line)
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
	else if (head.next && head.next->kind == TK_PIPE)
	{
		syntax_error("|\n", &line, line);
		g_return_error.tokenize_error = true;
	}
}

t_tk	*tokenize(char *line)
{
	t_tk	head;
	t_tk	*token;

	token = &head;
	token->word = NULL;
	token->kind = TK_WORD;
	token->next = NULL;
	judge_kind_and_put(&token, line);
	if (!g_return_error.tokenize_error)
		error_token(token, head, line);
	token->next = token_new(NULL, TK_EOF);
	return (head.next);
}
