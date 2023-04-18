/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:11:26 by enogaWa           #+#    #+#             */
/*   Updated: 2023/04/11 17:21:02 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static int	go_home(t_env **env_list)
{
	t_env	*path;
	t_env	*rewrite_pwd;
	char	*pwd_new;
	int		status;
	char	*old_pwd;

	status = 0;
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
	pwd_new = wrap_getcwd(NULL, 0);
	rewrite_pwd = search_env("PWD", *env_list);
	if (!rewrite_pwd)
		add_env(strjoin("PWD", pwd_new), env_list);
	free(rewrite_pwd->value);
	rewrite_pwd->value = pwd_new;
	path = search_env("OLDPWD", *env_list);
	if (!path)
		add_env(strjoin("OLDPWD", old_pwd), env_list);
	free(path->value);
	path->value = old_pwd;
	return (status);
}

static int	go_back_prev(t_env **env_list)
{
	t_env	*path;
	char	*old_pwd;
	t_env	*rewrite_pwd;
	char	*pwd_new;
	int		status;

	status = 0;
	old_pwd = wrap_getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	path = search_env("OLDPWD", *env_list);
	if (!path)
	{
		cd_error("OLDPWD");
		add_env(strjoin("OLDPWD=", old_pwd), env_list);
		return (1);
	}
	status = wrap_chdir(path->value);
	if (status == -1)
	{
		free(old_pwd);
		return (status);
	}
	pwd_new = wrap_getcwd(NULL, 0);
	rewrite_pwd = search_env("PWD", *env_list);
	if (!rewrite_pwd)
		add_env(strjoin("PWD", pwd_new), env_list);
	free(rewrite_pwd->value);
	rewrite_pwd->value = pwd_new;
	free(path->value);
	path->value = old_pwd;
	return (status);
}

static int	manage_cd_path(char *destination, t_env **env_list)
{
	t_env	*path;
	char	*old_pwd;
	t_env	*rewrite_pwd;
	char	*pwd_new;
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
	pwd_new = wrap_getcwd(NULL, 0);
	rewrite_pwd = search_env("PWD", *env_list);
	if (!rewrite_pwd)
		add_env(strjoin("PWD", pwd_new), env_list);
	free(rewrite_pwd->value);
	rewrite_pwd->value = pwd_new;
	path = search_env("OLDPWD", *env_list);
	if (!path)
		add_env(strjoin("OLDPWD", old_pwd), env_list);
	free(path->value);
	path->value = old_pwd;
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
