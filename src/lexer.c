/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogawa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:12:12 by enogawa           #+#    #+#             */
/*   Updated: 2022/12/22 11:27:11 by enogawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	find_next_quot(char *input, int i)
{
	char	c;
	int		len;

	c = input[i];
	len = 0;
	while (input[i + len])
	{
		if (input[i + len + 1] == c)
			return (len + 1);
		len++;
	}
	return (0);
}

static	int	split_count(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!input)
		return (1);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"' )
		{
			if (find_next_quot(input, i))
			{
				i += find_next_quot(input, i);
				count += 2;
			}
		}
		i++;
	}
	return (count + 2);
}

static	char	**split_by_quot(char *input)
{
	int		i;
	int		j;
	int		count;
	int		start;
	int		split_len;
	char	**tmp;

	i = 0;
	j = 0;
	start = 0;
	count = split_count(input);
	tmp = malloc(sizeof(char **) * count);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"' )
		{
			split_len = find_next_quot(input, i);
			if (split_len)
			{
				if ((input[i - 1] != '"' && input[i - 1] != '\'') && i != 0)
				{
					tmp[j] = ft_substr(input, start, (i - start));
					j++;
				}
				start = i;
				tmp[j] = ft_substr(input, start, split_len + 1);
				start += (split_len + 1);
				i += split_len;
				j++;
			}
		}
		i++;
	}
	if (i != start)
	{
		tmp[j] = ft_substr(input, start, i - start);
		j++;
	}
	tmp[j] = NULL;
	return (tmp);
}

int	lexer(char *input)
{
	char	**tmp;
	int		split_count;
	int		i;

	i = 0;
	
	tmp = split_by_quot(input);
	while (tmp[i])
	{
		printf("tmp: %s\n", tmp[i]);
		i++;
	}
	return (0);
}

	// t_cmd_lst	*separated;
	// separated = ft_calloc(1, sizeof(t_cmd_lst));
	// tmp = split_by_pipe(input, separated);
	// split_by_space(tmp, separated);