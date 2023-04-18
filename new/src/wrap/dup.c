/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:25:24 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/12 20:31:56 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	wrap_dup(int oldfd)
{
	int	result;

	result = dup(oldfd);
	if (result == -1)
	{
		perror(NULL);
		assert_error("dup\n");
	}
	return (result);
}
