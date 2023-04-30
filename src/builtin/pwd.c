/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:18:49 by enogaWa           #+#    #+#             */
/*   Updated: 2023/04/29 20:42:08 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

int	builtin_pwd(void)
{
	char	*pwd_path;

	pwd_path = wrap_getcwd(NULL, 0);
	if (pwd_path == NULL)
		return (1);
	write(1, pwd_path, strlen(pwd_path));
	write(1, "\n", 1);
	free(pwd_path);
	return (0);
}
