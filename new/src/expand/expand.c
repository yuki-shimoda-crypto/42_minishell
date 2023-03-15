/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:46:02 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/13 11:54:42 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>
#include <stdlib.h>


char	*expand_special_char(char **skipped, char *word, char *new_word)
{
	char *append_word;
	char *tmp;

	append_word = itoa(g_return_error.return_value);
	if (!append_word)
		assert_error("itoa\n");
	tmp = strjoin(new_word, append_word);
	if (!tmp)
		assert_error("strjoin\n");
	free(new_word);
	free(append_word);
	new_word = tmp;
	word++;
	word++;
	*skipped = word;
	return (new_word);
}

char	*append_char(char **skipped, char *word, char *new_word)
{
	char *append_word;
	char *tmp;

	append_word = strndup(word, 1);
	if (!append_word)
		assert_error("strndup\n");
	tmp = strjoin(new_word, append_word);
	free(new_word);
	free(append_word);
	new_word = tmp;
	word++;
	*skipped = word;
	return (new_word);
}

t_env	*find_word_expandable(const char *key, t_env *env_list)
{
	if (!key)
		return (NULL);
	while (env_list)
	{
		if (!strcmp(key, env_list->key))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*expand_variable(char **skipped, char *word, char *new_word, t_env *env_list)
{
	char	*head;
	char	*key;
	char	*value;
	char	*tmp;
	t_env	*target_list;

// ok
	word++;
	head = word;
	while (*word && is_alpha_num_under(*word))
		word++;
	key = strndup(head, word - head);
	if (!key)
		assert_error("strndup");
	target_list = find_word_expandable(key, env_list);
	free(key);
	if (target_list)
	{
		value = strdup(target_list->value);
		if (!value)
			assert_error("strdup\n");
	}
	else
	{
		value = calloc(1, sizeof(char));
		if (!value)
			assert_error("calloc\n");
	}
	tmp = strjoin(new_word, value);
	free(new_word);
	free(value);
	if (!tmp)
		assert_error("strjoin");
	new_word = tmp;
	*skipped = word;
	return (new_word);
}

//char	*expand_variable(char **skipped, char *word, char *new_word, t_env *env_list)
//{
//	char	*head;
//	char	*env;
//	char	*tmp;
//
//	word++;
//	head = word;
//	while (*word && is_alpha_num_under(*word))
//		word++;
//	env = strndup(head, word - head);
//	if (!env)
//		assert_error("strndup");
//	tmp = getenv(env);
//	free(env);
//	if (!tmp)
//	{
//		env = calloc(1, sizeof(char));
//		if (!env)
//			assert_error("calloc\n");
//	}
//	else
//	{
//		env = strdup(tmp);
//		if (!env)
//			assert_error("strndup");
//	}
//	tmp = strjoin(new_word, env);
//	free(new_word);
//	free(env);
//	if (!tmp)
//		assert_error("strjoin");
//	new_word = tmp;
//	*skipped = word;
//	return (new_word);
//}

char	*expand_double_quote(char **skipped, char *word, char *new_word, t_env *env_list)
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
		else if (is_variable(word))
		{
			append_word = strndup(head, word - head);
			if (!append_word)
				assert_error("strndup\n");
			tmp = strjoin(new_word, append_word);
			free(new_word);
			free(append_word);
			if (!tmp)
				assert_error("strjoin\n");
			new_word = tmp;
			new_word = expand_variable(&word, word, new_word, env_list);
			head = word;
		}
		else if (is_special_charactor(word))
		{
			append_word = strndup(head, word - head);
			if (!append_word)
				assert_error("strndup\n");
			tmp = strjoin(new_word, append_word);
			free(new_word);
			free(append_word);
			if (!tmp)
				assert_error("strjoin\n");
			new_word = tmp;
			new_word = expand_special_char(&word, word, new_word);
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

char	*expand_word(char *word, t_env *env_list)
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
			new_word = expand_double_quote(&word, word, new_word, env_list);
		else if (is_variable(word))
			new_word = expand_variable(&word, word, new_word, env_list);
		else if (is_special_charactor(word))
			new_word = expand_special_char(&word, word, new_word);
		else
			new_word = append_char(&word, word, new_word);
	}
	free(head);
	return (new_word);
}

void	expand_token(t_tk *token, t_env *env_list)
{
	if (!token)
		return ;
	token->word = expand_word(token->word, env_list);
	expand_token(token->next, env_list);
}

void	expand(t_node *node, t_env *env_list)
{
	if (!node)
		return ;
	expand_token(node->token, env_list);
	node->filename = expand_word(node->filename, env_list);
	expand(node->redirect, env_list);
	expand(node->pipe, env_list);
}
	
