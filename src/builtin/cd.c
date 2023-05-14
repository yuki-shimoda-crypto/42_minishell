/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:11:26 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/08 04:57:01 by yshimoda         ###   ########.fr       */
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
	status = wrap_chdir(path->value);
	if (status == -1)
		return (status);
	path = search_env("PWD", *env_list);
	if (!path || (path && !path->value))
		old_pwd = ft_strdup("");
	else
		old_pwd = ft_strdup(path->value);
	if (rewrite(old_pwd, env_list))
	{
		free(old_pwd);
		return (1);
	}
	return (status);
}

static int	go_back_prev(t_env **env_list)
{
	t_env	*path;
	char	*old_pwd;
	int		status;

	path = search_env("OLDPWD", *env_list);
	if (!path)
	{
		cd_error("OLDPWD");
		return (1);
	}
	status = wrap_chdir(path->value);
	if (status == -1)
		return (status);
	path = search_env("PWD", *env_list);
	if (!path || (path && !path->value))
		old_pwd = ft_strdup("");
	else
		old_pwd = ft_strdup(path->value);
	if (rewrite(old_pwd, env_list))
	{
		free(old_pwd);
		return (1);
	}
	return (status);
}

static int	manage_cd_path(char *destination, t_env **env_list)
{
	t_env	*path;
	char	*old_pwd;
	int		status;

	status = 0;
	status = wrap_chdir(destination);
	if (status == -1)
		return (status);
	path = search_env("PWD", *env_list);
	if (!path || (path && !path->value))
		old_pwd = ft_strdup("");
	else
		old_pwd = ft_strdup(path->value);
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
	else if (!ft_strcmp(destination[1], "-"))
		return (go_back_prev(env_list));
	status = manage_cd_path(destination[1], env_list);
	return (status);
}
