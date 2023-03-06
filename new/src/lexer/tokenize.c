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
#include <stdio.h>//
#include <unistd.h>//

t_return_error	g_return_error;

void	syntax_error(const char *msg, char **skipped, char *line)
{
	if (msg)
		write(STDERR_FILENO, msg, strlen(msg));
	while (*line)
		line++;
	*skipped = line;
}


void	assert_error(const char *msg)
{
	if (msg)
		write(STDERR_FILENO, msg, strlen(msg));
	exit(1);
}

			// token->next = pipe_into_list(&line, line);
t_tk	*pipe_into_list(char **skipped, char *line, t_tk *token)
{
	char	*word;

	if (token->kind == TK_PIPE)
		syntax_error("bash: syntax error near unexpected token '|'", &line, line);
	else
	{
		word = strndup(line, 1);
		if (!word)
			assert_error("strndup");
		line++;
		*skipped = line;
	}
	return (0);
}

t_tk	*word_into_list(char **skipped, char *line)
{
	char *word;
	char *start;

	start = line;
	while (*line)
	{
		if (is_blank(*line) && is_quote(*line)
			&& is_redirect(*line, skipped, line) && is_pipe(*line))
			break ;
		line++;
	}
	word = strndup(line, line - start);
	*skipped = line;
	return (token_new(word, TK_WORD));
}


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
		return (word_into_list(&line, line));
	else
	{
		word = strndup(start, line - start);
		*skipped = line;
	}
	return (token_new(word, TK_REDIRECT));
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
bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
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

bool	is_redirect(char c, char **skipped, char *line)
{
	if (is_redirect_error(line))
	{
		syntax_error("bash: syntax error near unexpected token ", skipped, line);
		g_return_error.tokenize_error = true;
	}
	else if (!strncmp(line, ">>", 2) || !strncmp(line, "<<", 2))
		return (true);
	return (c == '>' || c == '<');
}

// ok
bool	is_pipe(char c)
{
	return (c == '|');
}

t_tk	*tokenize(char *line)
{
	t_tk	*token;
	t_tk	*head;

	token = calloc(1, sizeof(t_tk));
	if (!token)
		assert_error("calloc");
	head = token;
	token->next = NULL;
	while (*line)
	{
		if (is_blank(*line))
			skip_blank(&line, line);//ok
		else if (is_quoted(*line, line))
		{
			token->next = quoted_into_list(&line, line, *line);
			token = token->next;
		}
//		else if (is_redirect(*line, &line, line))
//		{
//			token->next = redirect_into_list(&line, line, *line);
//			token = token->next;
//		}
//		else if (is_pipe(*line))
//		{
//			token->next = pipe_into_list(&line, line, token);
//			token = token->next;
//		}
//		else
//		{
//			token->next = word_into_list(&line, line);
//			token = token->next;
//		}
		else
			line++;
	}
	token->next = token_new(NULL, TK_EOF);
	return (head->next);
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