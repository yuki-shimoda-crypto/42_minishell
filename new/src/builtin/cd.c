/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:11:26 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/14 17:10:22 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static int	go_home(t_env **env_list)
{
	t_env	*path;
	size_t	status;
	char	*old_pwd;

	status = 0;
	path = search_env("HOME", *env_list);
	old_pwd = wrap_getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	status = wrap_chdir(path->value);
	if (status == -1)
		return (status);
	path = search_env("OLDPWD", *env_list);
	if (!path)
		env_add(ft_strjoin("OLDPWD", old_pwd), env_list);
	free(path->value);
	path->value = old_pwd;
	free(old_pwd);
	return (status);
}

static int	go_back_prev(t_env **env_list)
{
	t_env	*path;
	char	*old_pwd;
	int		status;

	status = 0;
	old_pwd = wrap_getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	path = search_env("OLDPWD", *env_list);
	if (!path)
		env_add(ft_strjoin("OLDPWD", old_pwd), env_list);
	status = wrap_chdir(path->value);
	free(path->value);
	path->value = old_pwd;
	free(old_pwd);
	return (status);
}

static int	manage_cd_path(char *destination, t_env **env_list)
{
	t_env	*path;
	char	*old_pwd;
	int		status;

	status = 0;
	old_pwd = wrap_getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	status = wrap_chdir(destination);
	if (status == -1)
		return (status);
	path = search_env("OLDPWD", *env_list);
	if (!path)
		env_add(ft_strjoin("OLDPWD", old_pwd), env_list);
	free(path->value);
	path->value = old_pwd;
	free(old_pwd);
	return (status);
}	

int	cd(char **destination, t_env **env_list)
{
	size_t	args;
	int		status;
	char	*old_pwd;

	args = 0;
	while (destination[args])
		args++;
	if (args == 1)
		return (go_home(env_list));
	else if (destination[1] == '-')
		return (go_back_prev(env_list));
	status = manage_cd_path(destination[1], env_list);
	return (status);
}

int main(void)
{
	char	*argv[] = {"cd", NULL};

	cd(argv, )
}