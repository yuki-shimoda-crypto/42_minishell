/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:12:53 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/14 17:25:01 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

char	*wrap_getcwd(char *buf, size_t size)
{
	size = PATH_MAX;
	while (1)
	{
		buf = malloc(sizeof(char) * size);
		if (!buf)
		{
			perror("NULL");
			assert_error("malloc\n");
		}
		if (getcwd(buf, size) != NULL)
			break ;
		if (errno != ERANGE)
		{
			perror("NULL");
			return (NULL);
		}
		size *= 2;
		free(buf);
	}
	return (buf);
}
