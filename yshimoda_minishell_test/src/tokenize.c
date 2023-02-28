/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:24:02 by yshimoda          #+#    #+#             */
/*   Updated: 2023/02/23 18:49:21 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = calloc(1, sizeof(*tok));
	if (tok == NULL)
		fatal_error("calloc");
	tok->word = word;
	tok->kind = kind;
	return(tok);
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	consume_blank(char	**rest, char *line)
{
	if (is_blank(*line))
	{
		while (*line && is_blank(*line))
			line++;
		*rest = line;
		return (true);
	}
	*rest = line;
	return (false);
}

bool	startswith(const char *s, const char *keyword)
{
	return (memcmp(s, keyword, strlen(keyword)) == 0);
}

bool	is_control_operator(const char *s)
{
	static char	const	*operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i = 0;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(s, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	is_redirection_operator(const char *s)
{
	static char const	*operators[] = {">", "<", ">>", "<<"};
	size_t				i = 0;
	
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(s, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	is_metacharacter(char c)
{
	if (is_blank(c))
		return (true);
	return (c && strchr("|&;()<>\t", c));
}

bool	is_word(const char *s)
{
	return (*s && !is_metacharacter(*s));
}

t_token	*operator(char **rest, char *line)
{
	static char	*const	operators[] = {">>", "<<", "||", "&&", ";;", "<", ">", "&", ";", "(", ")", "|", "\n"};
	size_t				i = 0;
	char				*op;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(line, operators[i]))
		{
			op = strdup(operators[i]);
			if (op == NULL)
				fatal_error("strdup");
			*rest = line + strlen(op);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	assert_error("Unexpected operator");
	return (NULL);
}

t_token	*word(char **rest, char *line)
{
	const char	*start = line;
	char		*word;

	while (*line && !is_metacharacter(*line))
	{
		if (*line == SINGLE_QUOTE_CHAR)
		{
			line++;
			while (*line && *line != SINGLE_QUOTE_CHAR)
				line++;
			if (*line == '\0')
			{
				tokenize_error("Unclosed single quote", &line, line);
				break ;
			}
			else
				line++;
		}
		else if (*line == DOUBLE_QUOTE_CHAR)
		{
			line++;
			while (*line && *line != DOUBLE_QUOTE_CHAR)
				line++;
			if (*line == '\0')
			{
				tokenize_error("Unclosed double quote", &line, line);
				break ;
			}
			else
				line++;
		}
		else
			line++;
	}
	word = strndup(start, line - start);
	if (word == NULL)
		fatal_error("strndup");
	*rest = line;
	return (new_token(word, TK_WORD));
}


t_token	*tokenize(char *line)
{
	t_token		head;
	t_token		*tok;

	syntax_error = false;
	head.next = NULL;
	tok = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_metacharacter(*line))
			tok = tok->next = operator(&line, line);
		else if (is_word(line))
			tok = tok->next = word(&line, line);
		else
			tokenize_error("Unexpedted Token", &line, line);
	}
	tok->next = new_token(NULL, TK_EOF);
	return (head.next);
}

char	**tail_recursive(t_token *tok, int nargs, char **argv)
{
	char	**new_argv;

	if (tok == NULL || tok->kind == TK_EOF)
		return (argv);
	new_argv = realloc(argv, (nargs + 2) * sizeof(char *));
	if (new_argv != NULL)
		argv = new_argv;
	else
	{
		free(argv);
		argv = NULL;
		fatal_error("realloc");
	}
	argv[nargs] = strdup(tok->word);
	if (argv[nargs] == NULL)
		fatal_error("strdup");
	argv[nargs + 1] = NULL;
	return (tail_recursive(tok->next, nargs + 1, argv));
}

char	**token_list_to_argv(t_token *tok)
{
	char	**argv;

	argv = calloc(1, sizeof(char *));
	if (argv == NULL)
		fatal_error("calloc");
	return (tail_recursive(tok, 0, argv));
}

