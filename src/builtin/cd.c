/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:11:26 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/06 18:22:38 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static int	go_home(t_env **env_list)
{
	t_env	*path;
	int		status;
	char	*old_pwd;

	path = search_env("HOME", *env_list);
	if (!path)
	{
		cd_error("HOME");
		return (1);
	}
	old_pwd = wrap_getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	status = wrap_chdir(path->value);
	if (status == -1)
	{
		free(old_pwd);
		return (status);
	}
	if (rewrite(old_pwd, env_list))
	{
		free(old_pwd);
		return (1);
	}
	return (status);
}

static int	free_return(int status, t_env *path, char *old_pwd)
{
	free(path);
	free(old_pwd);
	return (status);
}

static int	go_back_prev(t_env **env_list)
{
	t_env	*path;
	char	*old_pwd;
	int		status;

	old_pwd = wrap_getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	path = search_env("OLDPWD", *env_list);
	if (!path)
	{
		cd_error("OLDPWD");
		join_add_env("OLDPWD=", old_pwd, env_list);
		return (1);
	}
	status = wrap_chdir(path->value);
	if (status == -1)
		return (free_return(status, path, old_pwd));
	if (rewrite_go_back(old_pwd, env_list, path))
		return (free_return(1, path, old_pwd));
	return (status);
}

static int	manage_cd_path(char *destination, t_env **env_list)
{
	char	*old_pwd;
	int		status;

	status = 0;
	old_pwd = wrap_getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	status = wrap_chdir(destination);
	if (status == -1)
	{
		free(old_pwd);
		return (status);
	}
	if (rewrite(old_pwd, env_list))
	{
		free(old_pwd);
		return (1);
	}
	return (status);
}

int	builtin_cd(char **destination, t_env **env_list)
{
	size_t	args;
	int		status;

	args = 0;
	while (destination[args])
		args++;
	if (args == 1)
		return (go_home(env_list));
	else if (!strcmp(destination[1], "-"))
		return (go_back_prev(env_list));
	status = manage_cd_path(destination[1], env_list);
	return (status);
}
