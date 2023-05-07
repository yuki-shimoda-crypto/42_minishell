/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:46:02 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 14:36:50 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>
#include <stdlib.h>

// char	*expand_special_char(char **skipped, char *word, char *new_word)
// {
// 	char	*append_word;
// 	char	*tmp;

// 	append_word = itoa(g_return_error.return_value);
// 	if (!append_word)
// 		assert_error("itoa\n");
// 	tmp = strjoin(new_word, append_word);
// 	if (!tmp)
// 		assert_error("strjoin\n");
// 	free(new_word);
// 	free(append_word);
// 	new_word = tmp;
// 	word++;
// 	word++;
// 	*skipped = word;
// 	return (new_word);
// }

// char	*append_char(char **skipped, char *word, char *new_word)
// {
// 	char	*append_word;
// 	char	*tmp;

// 	append_word = ft_strndup(word, 1);
// 	if (!append_word)
// 		assert_error("ft_strndup\n");
// 	tmp = strjoin(new_word, append_word);
// 	free(new_word);
// 	free(append_word);
// 	new_word = tmp;
// 	word++;
// 	*skipped = word;
// 	return (new_word);
// }

// t_env	*find_word_expandable(const char *key, t_env *env_list)
// {
// 	if (!key)
// 		return (NULL);
// 	while (env_list)
// 	{
// 		if (!ft_strcmp(key, env_list->key))
// 			return (env_list);
// 		env_list = env_list->next;
// 	}
// 	return (NULL);
// }

// char	*make_expanded_word(char *new_word, t_env *target_list)
// {
// 	char	*tmp;
// 	char	*value;

// 	if (target_list)
// 	{
// 		value = ft_strdup(target_list->value);
// 		if (!value)
// 			assert_error("ft_strdup\n");
// 	}
// 	else
// 	{
// 		value = ft_calloc(1, sizeof(char));
// 		if (!value)
// 			assert_error("ft_calloc\n");
// 	}
// 	tmp = strjoin(new_word, value);
// 	free(new_word);
// 	free(value);
// 	if (!tmp)
// 		assert_error("strjoin");
// 	return (tmp);
// }

// char	*expand_variable(char **skipped, char *word,
// 							char *new_word, t_env *env_list)
// {
// 	char	*head;
// 	char	*key;
// 	t_env	*target_list;

// 	word++;
// 	head = word;
// 	while (*word && is_alpha_num_under(*word))
// 		word++;
// 	key = ft_strndup(head, word - head);
// 	if (!key)
// 		assert_error("ft_strndup");
// 	target_list = find_word_expandable(key, env_list);
// 	free(key);
// 	new_word = make_expanded_word(new_word, target_list);
// 	*skipped = word;
// 	return (new_word);
// }

// char	*make_new_word(char *head, char *word,
// 						char *append_word, char *new_word)
// {
// 	char	*tmp;

// 	append_word = ft_strndup(head, word - head);
// 	if (!append_word)
// 		assert_error("ft_strndup\n");
// 	tmp = strjoin(new_word, append_word);
// 	free(new_word);
// 	free(append_word);
// 	if (!tmp)
// 		assert_error("strjoin\n");
// 	new_word = tmp;
// 	return (new_word);
// }

// char	*sp_chara_expand(char **head, char **word,
// 							char *append_word, char *new_word)
// {
// 	new_word = make_new_word(*head, *word, append_word, new_word);
// 	new_word = expand_special_char(word, *word, new_word);
// 	*head = *word;
// 	return (new_word);
// }

// char	*expand_db_quote(char **skipped, char *word,
// 							char *new_word, t_env *env_list)
// {
// 	char	*head;
// 	char	*append_word;

// 	append_word = NULL;
// 	word++;
// 	head = word;
// 	while (*word)
// 	{
// 		if (*word == '"')
// 			break ;
// 		else if (is_variable(word))
// 		{
// 			new_word = make_new_word(head, word, append_word, new_word);
// 			new_word = expand_variable(&word, word, new_word, env_list);
// 			head = word;
// 		}
// 		else if (is_special_charactor(word))
// 			new_word = sp_chara_expand(&head, &word, append_word, new_word);
// 		else
// 			word++;
// 	}
// 	new_word = make_new_word(head, word, append_word, new_word);
// 	word++;
// 	*skipped = word;
// 	return (new_word);
// }

// char	*expand_single_quote(char **skipped, char *word, char *new_word)
// {
// 	char	*head;
// 	char	*appended_word;
// 	char	*tmp;

// 	word++;
// 	head = word;
// 	while (*word)
// 	{
// 		if (*word == '\'')
// 			break ;
// 		word++;
// 	}
// 	appended_word = ft_strndup(head, word - head);
// 	if (!appended_word)
// 		assert_error("ft_strndup\n");
// 	tmp = strjoin(new_word, appended_word);
// 	if (!tmp)
// 		assert_error("strjoin\n");
// 	free(appended_word);
// 	free(new_word);
// 	new_word = tmp;
// 	word++;
// 	*skipped = word;
// 	return (new_word);
// }

char	*skip_db_quote(char **skipped, char *word, char *new_word)
{
	char	*append_word;
	char	*head;
	char	*tmp;

	word++;
	head = word;
	while (*word != '"')
		word++;
	append_word = ft_strndup(head, word - head);
	if (!append_word)
		assert_error("ft_strndup\n");
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

char	*db_quote_new_word(char **word, t_node_kind kind,
							char *new_word, t_env *env_list)
{
	if (kind == ND_REDIRECT_HEREDOC)
		new_word = skip_db_quote(word, *word, new_word);
	else
		new_word = expand_db_quote(word, *word, new_word, env_list);
	return (new_word);
}

char	*expand_word(char *word, t_node_kind kind, t_env *env_list)
{
	char	*head;
	char	*new_word;

	if (!word)
		return (NULL);
	head = word;
	new_word = ft_calloc(1, sizeof(char));
	if (!new_word)
		assert_error("ft_calloc\n");
	while (*word)
	{
		if (is_single_quote(*word))
			new_word = expand_single_quote(&word, word, new_word);
		else if (is_double_quote(*word))
			new_word = db_quote_new_word(&word, kind, new_word, env_list);
		else if (is_variable(word) && kind != ND_REDIRECT_HEREDOC)
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
	token->word = expand_word(token->word, ND_SIMPLE_CMD, env_list);
	expand_token(token->next, env_list);
}

void	expand(t_node *node, t_env *env_list)
{
	if (!node)
		return ;
	expand_token(node->token, env_list);
	if (node->filename
		&& (ft_strchr(node->filename, '"') || ft_strchr(node->filename, '\'')))
		node->quote_flag = true;
	node->filename = expand_word(node->filename, node->kind, env_list);
	expand(node->redirect, env_list);
	expand(node->pipe, env_list);
}
