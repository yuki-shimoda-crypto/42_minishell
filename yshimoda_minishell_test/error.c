/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:32:03 by yshimoda          #+#    #+#             */
/*   Updated: 2023/02/22 09:03:13 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	assert_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Assert Error: %s\n", msg);
	exit(255);
}

void	err_exit(const char *location, const char *msg, int status)
{
	dprintf(STDERR_FILENO, "minishell: %s: %s \n", location, msg);
	exit(status);
}

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

void	todo(const char *msg)
{
	dprintf(STDERR_FILENO, "TODO: %s\n", msg);
	exit(255);
}
