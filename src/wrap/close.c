/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:38:57 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 02:17:23 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	wrap_close(int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == -1)
	{
		perror("close");
		g_return_error.error = true;
	}
	return (ret);
}
