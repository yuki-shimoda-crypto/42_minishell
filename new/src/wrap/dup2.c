/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:25:54 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/16 13:06:23 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	wrap_dup2(int oldfd, int newfd)
{
	int	result;

	result = dup2(oldfd, newfd);
	if (result == -1)
	{
		perror(NULL);
		assert_error("dup2\n");
	}
	return (result);
}
