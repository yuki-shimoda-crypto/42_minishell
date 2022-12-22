/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:12:12 by enogawa           #+#    #+#             */
/*   Updated: 2022/12/22 19:26:23 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	character_skip_redirect(char *input, const char c, size_t *i, size_t *count)
// {
// 	size_t	j;

// 	j = 0;
// 	while (input[*i] && input[*i] == c)
// 	{
// 		*i += 1;
// 		j++;
// 	}
// 	if (2 < j)
// 		error_func("syntax error");
// 	*count += 1;
// 	return ;
// }

static void	character_skip_quote(char *input, const char c, size_t *i, size_t *count)
{
	size_t	save;

	save = *i;
	*i += 1;
	if (save == 0)
		*count += 1;
	else if (ft_isspace(input[save - 1]) || input[save - 1] == '<' || input[save - 1] == '>' || input[save - 1] == '|')
		*count += 1;
	while (input[*i] && input[*i] != c)
		*i += 1;
	if (!input[*i])
		*i = save + 1;
	return ;
}

static size_t	word_count(char *input)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			character_skip_quote(input, input[i], &i, &count);
		// else if (input[i] == '>' || input[i] == '<')
		// 	character_skip_redirect(input, input[i], &i, &count);
		else
			i++;
	}
	printf("%zu\n", count);
	return (count);
}

int	lexer(char *input)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * (word_count(input) + 1));
	if (!cmd)
		error_func("malloc error");
	return (0);
}

// static char	**ft_free(char **ret, size_t len)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		free(ret[i]);
// 		ret[i] = NULL;
// 		i++;
// 	}
// 	free(ret);
// 	return (NULL);
// }

// static char	**make_ret(char const *s, char c, char **ret)
// {
// 	char const	*head;
// 	char const	*tail;
// 	size_t		i;

// 	i = 0;
// 	while (*s)
// 	{
// 		if (*s != c)
// 		{
// 			head = s;
// 			while (*s != c && *s)
// 				s++;
// 			tail = s;
// 			ret[i] = ft_strndup(head, tail - head);
// 			if (!ret[i])
// 				return (ft_free(ret, i));
// 			i++;
// 		}
// 		else
// 			s++;
// 	}
// 	ret[i] = NULL;
// 	return (ret);
// }

// static size_t	word_count(char const *s, char c)
// {
// 	size_t	words;

// 	words = 0;
// 	while (*s)
// 	{
// 		if (*s != c)
// 		{
// 			words++;
// 			while (*s != c && *s)
// 				s++;
// 		}
// 		else
// 			s++;
// 	}
// 	return (words);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**ret;

// 	if (!s)
// 		return (NULL);
// 	ret = malloc(sizeof(char *) * (word_count(s, c) + 1));
// 	if (!ret)
// 		return (NULL);
// 	ret = make_ret(s, c, ret);
// 	return (ret);
// }
