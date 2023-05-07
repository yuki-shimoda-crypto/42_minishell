/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   into_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 02:26:51 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 14:15:30 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tk	*pipe_into_list(char **skipped, char *line, t_tk *token)
{
	char	*word;

	word = NULL;
	if (token && (token->kind == TK_PIPE || token->kind == TK_REDIRECT))
	{
		syntax_error("'|'\n", skipped, line);
		g_return_error.tokenize_error = true;
	}
	else
	{
		word = ft_strndup(line, 1);
		if (!word)
			assert_error("ft_strndup\n");
		line++;
		*skipped = line;
	}
	return (token_new(word, TK_PIPE));
}

t_tk	*word_into_list(char **skipped, char *line)
{
	char	*word;
	char	*start;
	char	quote;

	start = line;
	while (*line && !is_blank(*line) && !is_redirect(*line, &line, line)
		&& !is_pipe(*line))
	{
		if (is_quote(*line))
		{
			if (is_quoted(*line, &line, line))
			{
				quote = *line;
				line++;
				while (*line != quote)
					line++;
				line++;
			}
		}
		else
			line++;
	}
	word = ft_strndup(start, line - start);
	*skipped = line;
	return (token_new(word, TK_WORD));
}

t_tk	*redirect_into_list(char **skipped,
			char *line, const char c, t_tk *token)
{
	char	*start;
	char	*word;

	if (token && token->kind == TK_REDIRECT)
	{
		syntax_error("< or >\n", skipped, line);
		g_return_error.tokenize_error = true;
		word = NULL;
	}
	else
	{
		start = line;
		while (*line == c)
			line++;
		word = ft_strndup(start, line - start);
		*skipped = line;
	}
	return (token_new(word, TK_REDIRECT));
}

static void	skip_while_quote(char **skipped, char *line)
{
	char	quote;

	quote = *line;
	line++;
	while (*line != quote)
		line++;
	line++;
	*skipped = line;
}

t_tk	*quoted_into_list(char **skipped, char *line, const char c)
{
	char	*start;
	char	*word;

	start = line;
	line++;
	while (*line != c)
		line++;
	line++;
	while (*line && !is_blank(*line) && !is_redirect(*line, &line, line)
		&& !is_pipe(*line))
	{
		if (is_quote(*line))
		{
			if (is_quoted(*line, &line, line))
				skip_while_quote(&line, line);
		}
		else
			line++;
	}
	word = ft_strndup(start, line - start);
	*skipped = line;
	return (token_new(word, TK_WORD));
}
