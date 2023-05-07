/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:18:49 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 14:14:18 by yshimoda         ###   ########.fr       */
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
	write(1, pwd_path, ft_strlen(pwd_path));
	write(1, "\n", 1);
	free(pwd_path);
	return (0);
}
