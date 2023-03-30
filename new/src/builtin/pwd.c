/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:18:49 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/30 18:03:43 by enogaWa          ###   ########.fr       */
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
	printf("%s\n", pwd_path);
	free(pwd_path);
	return (0);
}
