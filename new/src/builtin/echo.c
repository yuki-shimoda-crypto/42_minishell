/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:19:57 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/13 18:50:56 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void	echo(char **argv)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		wrap_write(1, argv[i], strlen(argv[i]));
		wrap_write(1, " ", 1);
		i++;
	}
	wrap_write(1, "\n", 1);
}
