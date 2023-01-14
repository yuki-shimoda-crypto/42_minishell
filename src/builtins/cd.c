/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogawa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 03:19:18 by enogawa           #+#    #+#             */
/*   Updated: 2023/01/14 15:54:01 by enogawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	go_home(t_env_list *env_box)
{
	t_env_list	*path;
	size_t		status;
	char		*old_pwd;

	path = search_env("HOME", env_box);
	old_pwd = getcwd(NULL, 0);
	status = chdir(path->value);
	if (status == -1)
		ft_putendl_fd("bash: cd: HOME not set", STDERR_FILENO);
	path = search_env("OLDPWD", env_box);
	if (!path)
		env_add(ft_strjoin("OLDPWD", old_pwd), env_new());
	free(path->value);
	path->value = old_pwd;
	free(old_pwd);
	return (0);
}

static int	go_back_prev(t_env_list *env_box)
{
	t_env_list	*path;
	char		*old_pwd;
	int			status;

	old_pwd = getcwd(NULL, 0);
	path = search_env("OLDPWD", env_box);
	if (!path)
		ft_putendl_fd("cannot allocate memory", STDERR_FILENO);
	status = chdir(path->value);
	if (status == -1)
		ft_putendl_fd("bash: cd: HOME not set", STDERR_FILENO);
	free(path->value);
	path->value = old_pwd;
	free(old_pwd);
	return (0);
}

static int	manage_cd_path(char *destination, t_env_list *env_box)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		ft_putendl_fd("cannot allocate memory", STDERR_FILENO);
		return (1);
	}
}	

int	cd(char **destination, t_env_list *env_box)
{
	size_t	args;
	int		status;
	char	*old_pwd;

	args = 0;
	while (destination[args])
		args++;
	if (args == 1)
		return (go_home(env_box));
	else if (destination[1] == '-')
		return (go_back_prev(env_box));
	status = manage_cd_path(destination, env_box);
	return (status);
}
