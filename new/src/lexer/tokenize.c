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

t_tk	*token_new(char *word, t_tk_kind kind)
{
	t_tk	*token;

	token = calloc(1, sizeof(t_tk));
	if (!token)
		assert_error("calloc");
	token->word = word;
	token->kind = kind;
	return (token);
}

t_tk	*redirect_into_list(char **skipped, char *line, const char c)
{
	char	*word;
	char	*start;

	start = line;
	while (*line)
	{
		if (*line != c)
		line++;
	}
	if (line - start > 2)
		return (word_into_list());
	else
	{
		word = strndup(start, line - start);
		*skipped = line;
	}
	return (token_new(word, TK_OPERATOR));
}

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

// ok
bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

// ok
void	skip_blank(char **skipped, char *line)
{
	while (is_blank(*line))
		line++;
	*skipped = line;
}

// ok
bool	is_quoted(char c, char *line)
{
	if (c == '\'' || c == '"')
	{
		while (*line)
		{
			line++;
			if (*line == c)
				return (true);
		}
	}
	return (false);
}

bool	is_redirect_error(char *line)
{
	if (!strncmp(line, ">>>", 3))
		return (true);
	else if (!strncmp(line, "<<<", 3))
		return (true);
	else if (!strncmp(line, ">><", 3))
		return (true);
	else if (!strncmp(line, "<<>", 3))
		return (true);
	else if (!strncmp(line, "<>", 2))
		return (true);
	else if (!strncmp(line, "><", 2))
		return (true);
	return (false);
}

bool	is_redirect(char c, char *line, char **skipped)
{
	if (is_redirect_error(line))
	{
		syntax_error("bash: syntax error near unexpected token `%c'", *line);
		while (*line)
			line++;
		*skipped = line;
		g_return_error.tokenize_error = true;
	}
	else if (!strncmp(line, ">>", 2) || !strncmp(line, "<<", 2))
		return (true);
	return (c == '>' | c == '<');
}

bool	is_pipe(char c)
{
	return (c == '|');
}

void	tokenize(t_tk *token, char *line)
{
	while (*line)
	{
		if (is_blank(*line))
			skip_blank(&line, line);//ok
		else if (is_quoted(*line, line))
		{
			token->next = quoted_into_list(&line, line, *line);
			token = token->next;
		}
		else if (is_redirect(*line, line))
		{
			token->next = redirect_into_list(&line, line);
			token = token->next;
		}
		else if (is_pipe(*line))
		{
			token->next = pipe_into_list(&line, line);
			token = token->next;
		}
		else
		{
			token->next = word_into_list(&line, line);
			token = token->next;
		}
	}
	token->next = token_new(NULL, TK_EOF);
	token = token->next;
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
//