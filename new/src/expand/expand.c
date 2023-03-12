/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:46:02 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/13 02:59:23 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>
#include <stdlib.h>

bool	is_single_quote(const char c)
{
	return (c == '\'');
}

bool	is_double_quote(const char c)
{
	return (c == '"');
}

bool	is_special_charactor(char *line)
{
	return (line[0] == '$' && line[1] == '?');
}

bool	is_variable(char *line)
{
	return (line[0] == '$' && is_alpha_under(line[1]));
}

bool	is_expand(char *line)
{
	return (is_variable(line) || is_special_charactor(line));
}

bool	is_alpha_under(char c)
{
	return (isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || isdigit(c));
}

char	*append_char(const char c, char *new_word)
{
	char *append_word;
	char *tmp;

	append_word = calloc(2, sizeof(char));
	if (!append_word)
		assert_error("calloc\n");
	append_word[0] = c;
	tmp = strjoin(new_word, append_word);
	free(new_word);
	free(append_word);
	new_word = tmp;
	return (new_word);
}

char	*expand_variable(char **skipped, char *word, char *new_word)
{
	char	*head;
	char	*env;
	char	*tmp;

	word++;
	head = word;
	while (*word && is_alpha_num_under(*word))
		word++;
	env = strndup(head, word - head);
	if (!env)
		assert_error("strndup");
	tmp = getenv(env);
	free(env);
	if (!tmp)
	{
		env = calloc(1, sizeof(char));
		if (!env)
			assert_error("calloc\n");
	}
	else
	{
		env = strdup(tmp);
		if (!env)
			assert_error("strndup");
	}
	tmp = strjoin(new_word, env);
	free(new_word);
	free(env);
	if (!tmp)
		assert_error("strjoin");
	new_word = tmp;
	*skipped = word;
	return (new_word);
}

char	*expand_double_quote(char **skipped, char *word, char *new_word)
{
	char	*head;
	char	*tmp;
	char	*append_word;

	word++;
	head = word;
	while (*word)
	{
		if (*word == '"')
			break ;
		else if (is_expand(word))
		{
			append_word = strndup(head, word - head);
			if (!append_word)
				assert_error("strjoin\n");
			tmp = strjoin(new_word, append_word);
			free(new_word);
			free(append_word);
			if (!tmp)
				assert_error("strjoin\n");
			new_word = tmp;
			new_word = expand_variable(&word, word, new_word);
			head = word;
		}
		else
			word++;
	}
	append_word = strndup(head, word - head);
	if (!append_word)
		assert_error("strndup\n");
	tmp = strjoin(new_word, append_word);
	if (!tmp)
		assert_error("strjoin\n");
	free(append_word);
	free(new_word);
	new_word = tmp;
	word++;
	*skipped = word;
	return (new_word);
}

char	*expand_single_quote(char **skipped, char *word, char *new_word)
{
	char	*head;
	char	*appended_word;
	char	*tmp;

	word++;
	head = word;
	while (*word)
	{
		if (*word == '\'')
			break ;
		word++;
	}
	appended_word = strndup(head, word - head);
	if (!appended_word)
		assert_error("strndup\n");
	tmp = strjoin(new_word, appended_word);
	if (!tmp)
		assert_error("strjoin\n");
	free(appended_word);
	free(new_word);
	new_word = tmp;
	word++;
	*skipped = word;
	return (new_word);
}

char	*expand_word(char *word)
{
	char	*head;
	char	*new_word;

	if (!word)
		return (NULL);
	head = word;
	new_word = calloc(1, sizeof(char));
	if (!new_word)
		assert_error("calloc\n");
	while (*word)
	{
		if (is_single_quote(*word))
			new_word = expand_single_quote(&word, word, new_word);
		else if (is_double_quote(*word))
			new_word = expand_double_quote(&word, word, new_word);
		else if (is_expand(word))
			new_word = expand_variable(&word, word, new_word);
		else
		{
			new_word = append_char(*word, new_word);
			word++;
		}
	}
	free(head);
	return (new_word);
}

void	expand_token(t_tk *token)
{
	if (!token)
		return ;
	token->word = expand_word(token->word);
	expand_token(token->next);
}

void	expand(t_node *node)
{
	if (!node)
		return ;
	expand_token(node->token);
	node->filename = expand_word(node->filename);
	expand(node->redirect);
	expand(node->pipe);
}
	