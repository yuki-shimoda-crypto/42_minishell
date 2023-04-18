/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:24:50 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/16 13:06:43 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	wrap_pipe(int pipefd[2])
{
	int	result;

	result = pipe(pipefd);
	if (result == -1)
	{
		perror(NULL);
		assert_error("pipe\n");
	}
	return (result);
}
