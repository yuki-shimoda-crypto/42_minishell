/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogawa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:12:12 by enogawa           #+#    #+#             */
/*   Updated: 2022/12/23 21:27:29 by enogawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	free_tmp(char **tmp, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(tmp);
}

static	int	cpy_array(char *input, int start, int i, t_lexer_utils	*split_box)
{
	int	j;

	j = split_box->index;
	if (split_box->split_len)
	{
		if (split_box->flag || (input[i - 1] != '"' && input[i - 1] != '\''
				&& i != 0))
		{
			split_box->flag = 0;
			split_box->tmp[j] = ft_substr(input, start, (i - start));
			if (!split_box->tmp[j])
				free_tmp(split_box->tmp, j);
			j++;
		}
		start = i;
		split_box->tmp[j] = ft_substr(input, start, split_box->split_len + 1);
		if (!split_box->tmp[j])
			free_tmp(split_box->tmp, j);
		start += (split_box->split_len + 1);
		split_box->index = j + 1;
	}
	else
		split_box->flag = 1;
	return (start);
}

static	void	split_by_quot(char *input, t_lexer_utils	*split_box)
{
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"' )
		{
			split_box->split_len = find_next_quot(input, i);
			start = cpy_array(input, start, i, split_box);
			i += split_box->split_len;
		}
		i++;
	}
	if (i != start)
	{
		split_box->tmp[split_box->index] = ft_substr(input, start, i - start);
		if (!split_box->tmp[split_box->index])
			free_tmp(split_box->tmp, split_box->index);
		split_box->index++;
	}
	split_box->tmp[split_box->index] = NULL;
}

int	lexer(char *input)
{
	int				count;
	int				i;
	t_lexer_utils	*split_box;

	i = 0;
	split_box = ft_calloc(1, sizeof(t_lexer_utils));
	count = split_count(input);
	split_box->tmp = malloc(sizeof(char **) * count);
	if (!split_box->tmp)
		return (0);
	split_by_quot(input, split_box);
	while (split_box->tmp[i])
	{
		printf("tmp: %s\n", split_box->tmp[i]);
		i++;
	}
	return (0);
}
