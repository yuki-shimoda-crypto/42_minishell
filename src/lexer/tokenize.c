/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:13:24 by enogaWa           #+#    #+#             */
/*   Updated: 2023/02/14 19:07:35 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list *new_token(char *word, t_tk_kind kind)
{
	t_token_list *tk_list;

	tk_list = calloc(1, sizeof(*tk_list));
	// if (tk_list == NULL)
	// 	fatal_error("calloc");
	tk_list->token = word;
	tk_list->kind = kind;
	return (tk_list);
}

static char *skip_quot(char *input, char quot)
{
	input++;
	while (*input != quot)
	{
		if (*input == '\0')
		{
			return (input);
			// write(2, "not quoted\n", 11);
		}
		input++;
	}
	input++;
	return (input);
}

static t_token_list *word_into_list(char **rest, char *input)
{
	char *start;
	char *word;

	start = input;
	while (*input && *input != ' ' && *input != '|')
	{
		if (*input == '\'')
			input = skip_quot(input, '\'');
		else if (*input == '"')
			input = skip_quot(input, '"');
		else
			input++;
	}
	word = ft_strndup(start, input - start);
	// if (!word)
	// 	fatal_error("strndup");
	*rest = input;
	return (new_token(word, TK_WORD));
}

static bool is_pipe(char *input)
{
	if (*input == '|')
		return (true);
	return (false);
}

static void skip_space(char **rest, char *input)
{
	if (*input == ' ' || *input == '\t' || *input == '\n')
	{
		while (*input && (*input == ' ' || *input == '\t' || *input == '\n'))
			input++;
		*rest = input;
	}
}

static t_token_list *tokenize(char *input)
{
	t_token_list head;
	t_token_list *tk_list;

	head.next = NULL;
	tk_list = &head;
	while (*input)
	{
		skip_space(&input, input);
		if (is_pipe(input))
		{
			tk_list->next = new_token("|", TK_PIPE);
			tk_list = tk_list->next;
			input++;
		}
		if (*input != '|' && *input != ' ')
		{
			tk_list->next = word_into_list(&input, input);
			tk_list = tk_list->next;
		}
	}
	tk_list->next = new_token(NULL, TK_EOF);
	return (head.next);
}

static bool check_quoted(char *token)
{
	// printf("token = %s\n",token);

	// printf("%d %d\n", token[0] == '\"', token[ft_strlen(token-1)] == '\"');
	if (!token)
		return (false);
	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
	{

		return (true);
	}
	if (token[0] == '"' && token[ft_strlen(token) - 1] == '"')
	{
		return (true);
	}
	return (false);
}

static void remove_quot(t_token_list *tk_list)
{
	char *tmp;

	if (tk_list->kind == TK_EOF)
		return;
	if (tk_list->kind == TK_WORD)
	{
		// printf("bool %d\n",check_quoted(tk_list->token));
		if (check_quoted(tk_list->token))
		{
			tmp = ft_substr(tk_list->token, 1, ft_strlen(tk_list->token) - 2);
			free(tk_list->token);
			tk_list->token = tmp;
		}
	}
	tk_list = tk_list->next;
	remove_quot(tk_list);
}

static void expand(t_token_list *tk_list)
{
	remove_quot(tk_list);
}

t_token_list *lexer(char *input)
{
	t_token_list *tk_list;

	tk_list = tokenize(input);
	expand(tk_list);
	return (tk_list);
}
