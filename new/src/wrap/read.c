/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:25:43 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/12 20:28:08 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

ssize_t	wrap_read(int fd, void *buf, size_t count)
{
	ssize_t	result;

	while (1)
	{
		result = read(fd, buf, count);
		if (result == -1 && errno == EINTR)
			continue ;
		else
			break ;
	}
	if (result == -1)
	{
		perror(NULL);
		assert_error("read\n");
	}
	return (result);
}
