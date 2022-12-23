/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogawa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:14:31 by enogawa           #+#    #+#             */
/*   Updated: 2022/12/22 22:30:22 by enogawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_count(char *input)
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

int	find_next_quot(char *input, int i)
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
