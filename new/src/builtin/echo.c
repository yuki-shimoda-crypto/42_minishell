/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:19:57 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/14 03:59:22 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void	builtin_echo(char **argv)
{
	size_t	i;

	i = 1;
	if (!strncmp(argv[1], "-n", 2))
		i++;
	while (argv[i])
	{
		wrap_write(1, argv[i], strlen(argv[i]));
		wrap_write(1, " ", 1);
		i++;
	}
	if (strncmp(argv[1], "-n", 2))
		wrap_write(1, "\n", 1);
}
