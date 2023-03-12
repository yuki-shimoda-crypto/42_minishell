/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:24:50 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/12 20:31:56 by yshimoda         ###   ########.fr       */
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
