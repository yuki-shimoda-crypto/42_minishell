/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:24:53 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 15:51:25 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char **skipped, char *word, char *new_word)
{
	char	*append_word;
	char	*tmp;

	append_word = ft_strndup(word, 1);
	if (!append_word)
		assert_error("ft_strndup\n");
	tmp = ft_strjoin(new_word, append_word);
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
		if (!ft_strcmp(key, env_list->key))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*make_expanded_word(char *new_word, t_env *target_list)
{
	char	*tmp;
	char	*value;

	if (target_list)
	{
		value = ft_strdup(target_list->value);
		if (!value)
			assert_error("ft_strdup\n");
	}
	else
	{
		value = ft_calloc(1, sizeof(char));
		if (!value)
			assert_error("ft_calloc\n");
	}
	tmp = ft_strjoin(new_word, value);
	free(new_word);
	free(value);
	if (!tmp)
		assert_error("ft_strjoin");
	return (tmp);
}

char	*make_new_word(char *head, char *word,
						char *append_word, char *new_word)
{
	char	*tmp;

	append_word = ft_strndup(head, word - head);
	if (!append_word)
		assert_error("ft_strndup\n");
	tmp = ft_strjoin(new_word, append_word);
	free(new_word);
	free(append_word);
	if (!tmp)
		assert_error("ft_strjoin\n");
	new_word = tmp;
	return (new_word);
}
