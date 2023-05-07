/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:24:24 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 14:34:54 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_special_char(char **skipped, char *word, char *new_word)
{
	char	*append_word;
	char	*tmp;

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

char	*expand_variable(char **skipped, char *word,
							char *new_word, t_env *env_list)
{
	char	*head;
	char	*key;
	t_env	*target_list;

	word++;
	head = word;
	while (*word && is_alpha_num_under(*word))
		word++;
	key = ft_strndup(head, word - head);
	if (!key)
		assert_error("ft_strndup");
	target_list = find_word_expandable(key, env_list);
	free(key);
	new_word = make_expanded_word(new_word, target_list);
	*skipped = word;
	return (new_word);
}

char	*sp_chara_expand(char **head, char **word,
							char *append_word, char *new_word)
{
	new_word = make_new_word(*head, *word, append_word, new_word);
	new_word = expand_special_char(word, *word, new_word);
	*head = *word;
	return (new_word);
}

char	*expand_db_quote(char **skipped, char *word,
							char *new_word, t_env *env_list)
{
	char	*head;
	char	*append_word;

	append_word = NULL;
	word++;
	head = word;
	while (*word)
	{
		if (*word == '"')
			break ;
		else if (is_variable(word))
		{
			new_word = make_new_word(head, word, append_word, new_word);
			new_word = expand_variable(&word, word, new_word, env_list);
			head = word;
		}
		else if (is_special_charactor(word))
			new_word = sp_chara_expand(&head, &word, append_word, new_word);
		else
			word++;
	}
	new_word = make_new_word(head, word, append_word, new_word);
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
	appended_word = ft_strndup(head, word - head);
	if (!appended_word)
		assert_error("ft_strndup\n");
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
