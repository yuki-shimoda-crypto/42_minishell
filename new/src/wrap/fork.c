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

pid_t	wrap_fork(void)
{
	pid_t	result;

	result = fork();
	if (result == -1)
	{
		perror(NULL);
		assert_error("fork\n");
	}
	return (result);
}
