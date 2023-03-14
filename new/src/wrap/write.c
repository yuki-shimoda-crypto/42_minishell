/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:24:50 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/12 20:28:31 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

ssize_t wrap_write(int fd, const void *buf, size_t count)
{
	ssize_t	result;
	
	result = write(fd, buf, count);
	if (result == -1)
	{
		perror(NULL);
		assert_error("pipe\n");
	}
	return (result);
}