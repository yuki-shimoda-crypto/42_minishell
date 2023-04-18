/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:47:43 by enogawa           #+#    #+#             */
/*   Updated: 2023/03/13 21:35:16 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pwd(void)
{
	char	*pwd_path;

	pwd_path = getcwd(NULL, 0);
	if (!pwd_path)
		error_func("failed to get pwd_path");
	ft_putendl_fd(pwd_path, STDOUT_FILENO);
}
