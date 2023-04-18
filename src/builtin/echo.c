/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:19:57 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/16 23:10:59 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void	builtin_echo(char **argv)
{
	size_t	i;

	if (!argv[1])
		wrap_write(STDOUT_FILENO, "\n", 1);
	else
	{
		i = 1;
		if (!strncmp(argv[1], "-n", 2))
			i++;
		while (argv[i])
		{
			wrap_write(STDOUT_FILENO, argv[i], strlen(argv[i]));
			if (argv[i + 1])
				wrap_write(STDOUT_FILENO, " ", 1);
			i++;
		}
		if (strncmp(argv[1], "-n", 2))
			wrap_write(STDOUT_FILENO, "\n", 1);
	}
}
