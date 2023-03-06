/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:52:17 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/04 20:01:220 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

// ok_yshimoda
t_tk	*pipe_into_list(char **skipped, char *line, t_tk *token)
{
	char	*word;

	word = NULL;
	if (token && token->kind == TK_PIPE)
	{
		syntax_error("bash: syntax error near unexpected token '|'\n", skipped, line);
		g_return_error.tokenize_error = true;
	}
	else
	{
		word = strndup(line, 1);
		if (!word)
			assert_error("strndup");
		line++;
		*skipped = line;
	}
	return (token_new(word, TK_PIPE));
}

t_tk	*word_into_list(char **skipped, char *line)
{
	char *word;
	char *start;

	start = line;
	while (*line)
	{
		if (is_blank(*line) || is_quote(*line)
			|| is_redirect(*line, skipped, line) || is_pipe(*line))
			break ;
		line++;
	}
	word = strndup(start, line - start);
	*skipped = line;
	return (token_new(word, TK_WORD));
}

// ok_yshimoda
t_tk	*token_new(char *word, t_tk_kind kind)
{
	t_tk	*token;

	token = calloc(1, sizeof(t_tk));
	if (!token)
		assert_error("calloc");
	token->word = word;
	token->kind = kind;
	token->next = NULL;
	return (token);
}

t_tk	*redirect_into_list(char **skipped, char *line, const char c, t_tk *token)
{
	char	*start;
	char	*word;

	if (token && token->kind == TK_REDIRECT)
	{
		syntax_error("bash: syntax error near unexpected token < or >\n", skipped, line);
		g_return_error.tokenize_error = true;
		word = NULL;
	}
	else
	{
		start = line;
		while (*line == c)
			line++;
		word = strndup(start, line - start);
		*skipped = line;
	}
	return (token_new(word, TK_REDIRECT));
}

// ok
t_tk	*quoted_into_list(char **skipped, char *line, const char c)
{
	char	*start;
	char	*word;

	line++;
	start = line;
	while (*line != c)
		line++;
	word = strndup(start, line - start);
	line++;
	*skipped = line;
	return (token_new(word, TK_WORD));
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
		else if (is_quoted(*line, line))
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
	token->next = NULL;
	return (head.next);
}

//#include <stdio.h>
//
//int main(void)
//{
//	char	line[100] = "      '42tokyo42tokyo";
//	char	*skipped;
//
//	printf("%s\n", line);
//	skip_blank(&skipped, line);
//	printf("%s\n", skipped);
//	// if (is_quoted(*line, line))
//	// 	printf("%s\n", "OK");
//	// else
//	// 	printf("%s\n", "NG");
//	return (0);
//}