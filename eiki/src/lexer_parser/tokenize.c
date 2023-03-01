/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:13:24 by enogaWa           #+#    #+#             */
/*   Updated: 2023/02/28 23:19:38 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list *new_token(char *word, t_tk_kind kind)
{
	t_token_list	*tk_list;

	tk_list = calloc(1, sizeof(*tk_list));
	// if (tk_list == NULL)
	// 	fatal_error("calloc");
	tk_list->token = word;
	tk_list->kind = kind;
	return (tk_list);
}

static char *skip_quote(char *input, char quote)
{
	input++;
	while (*input != quote)
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
		if (*input == '<' || *input == '>')
			break ;
		if (*input == '\'')
		{
			input = skip_quote(input, '\'');
			break ;
		}
		else if (*input == '"')
		{
			input = skip_quote(input, '"');
			break ;
		}
		else
			input++;
		if (*input == '\'' || *input == '"')
			break ;
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

static t_token_list	*ope_into_list(char **rest, char *input)
{
	char	*start;
	char	*word;

	start = input;
	while (*input == '<')
	{
		input++;
		if (*input == '>')
			exit (2);//error処理
	}
	while (*input == '>')
	{
		input++;
		if (*input == '<')
			exit (2);//error処理
	}
	word = ft_strndup(start, input - start);
	// if (!word)
	// 	fatal_error("strndup");
	if (ft_strlen(word) > 2)
		exit (2);//error処理
	*rest = input;
	return (new_token(word, TK_OP));
}

// static t_token_list	*get_cmd(char **rest, char *input)
// {
// 	char	*word;
// 	char	*start;

// 	start = input;
// 	while (*input != ' ')
// 		input++;
// 	word = ft_strndup(start, input - start);
// 	*rest = input;
// 	return (new_token(word, TK_WORD));
// }

static t_token_list *tokenize(char *input)
{
	t_token_list head;
	t_token_list *tk_list;

	head.next = NULL;
	tk_list = &head;
	// skip_space(&input, input);//
	// tk_list->next = get_cmd(&input, input);//
	// tk_list = tk_list->next;//
	while (*input != '\0')
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
			// if (tk_list->kind == TK_PIPE)
			// {
			// 	tk_list->next = get_cmd(&input, input);//
			// 	tk_list = tk_list->next;//
			// }
			tk_list->next = word_into_list(&input, input);
			tk_list = tk_list->next;
			skip_space(&input, input);
		}
		if (*input == '<' || *input == '>')
		{
			tk_list->next = ope_into_list(&input, input);
			tk_list = tk_list->next;
			// if (!ope_into_list(&input, input))
			// {
			// 	write(2, "error: <, >", 11);
			// 	exit(2);
			// 	// syntax_error("redirect");
			// }
		}
		if (tk_list->kind == TK_OP)
		{
			skip_space(&input, input);
			tk_list->next = word_into_list(&input, input);
			tk_list = tk_list->next;
			tk_list->kind = TK_FILE;
		}
	}
	tk_list->next = new_token(NULL, TK_EOF);
	return (head.next);
}

static bool check_quoted(char *token)
{
	if (!token)
		return (false);
	if ((token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
		|| (token[0] == '"' && token[ft_strlen(token) - 1] == '"'))
		return (true);
	return (false);
}

static void remove_quote(t_token_list *tk_list)
{
	char	*tmp;

	if (tk_list->kind == TK_EOF)
		return ;
	if (tk_list->kind == TK_WORD)
	{
		if (check_quoted(tk_list->token))
		{
			tmp = ft_substr(tk_list->token, 1, ft_strlen(tk_list->token) - 2);
			free(tk_list->token);
			tk_list->token = tmp;
		}
	}
	tk_list = tk_list->next;
	remove_quote(tk_list);
}

static void expand(t_token_list *tk_list)
{
	remove_quote(tk_list);
}

t_token_list *lexer(char *input)
{
	t_token_list	*tk_list;

	tk_list = tokenize(input);
	expand(tk_list);
	return (tk_list);
}
