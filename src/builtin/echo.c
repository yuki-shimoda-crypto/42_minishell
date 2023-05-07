/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:19:57 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 14:15:18 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static bool	is_output_newline(const char *word)
{
	size_t	i;

	if (ft_strncmp(word, "-n", 2))
		return (true);
	i = 1;
	while (word[i])
	{
		if (word[i] != 'n')
			return (true);
		i++;
	}
	return (false);
}

int	builtin_echo(char **argv)
{
	size_t	i;

	if (!argv[1])
		wrap_write(STDOUT_FILENO, "\n", 1);
	else
	{
		i = 1;
		if (!is_output_newline(argv[1]))
			i++;
		while (argv[i])
		{
			wrap_write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
			if (argv[i + 1])
				wrap_write(STDOUT_FILENO, " ", 1);
			i++;
		}
		if (is_output_newline(argv[1]))
			wrap_write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
