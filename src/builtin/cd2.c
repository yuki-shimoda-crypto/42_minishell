/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:51:51 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/06 18:26:21 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_add_env(char *key, char *value, t_env **env_list)
{
	char	*tmp;

	tmp = strjoin(key, value);
	if (!tmp)
		assert_error("strjoin\n");
	add_env(tmp, env_list);
	free(tmp);
	free(value);
}

int	rewrite_go_back(char *old_pwd, t_env **env_list, t_env *path)
{
	t_env	*rewrite_pwd;
	char	*pwd_new;

	pwd_new = wrap_getcwd(NULL, 0);
	if (!pwd_new)
		return (1);
	rewrite_pwd = search_env("PWD", *env_list);
	if (!rewrite_pwd)
		join_add_env("PWD=", pwd_new, env_list);
	else
	{
		free(rewrite_pwd->value);
		rewrite_pwd->value = pwd_new;
	}
	free(path->value);
	path->value = old_pwd;
	return (0);
}

int	rewrite(char *old_pwd, t_env **env_list)
{
	t_env	*path;
	t_env	*rewrite_pwd;
	char	*pwd_new;

	pwd_new = wrap_getcwd(NULL, 0);
	if (!pwd_new)
		return (1);
	rewrite_pwd = search_env("PWD", *env_list);
	if (!rewrite_pwd)
		join_add_env("PWD=", pwd_new, env_list);
	else
	{
		free(rewrite_pwd->value);
		rewrite_pwd->value = pwd_new;
	}
	path = search_env("OLDPWD", *env_list);
	if (!path)
		join_add_env("OLDPWD=", old_pwd, env_list);
	else
	{
		free(path->value);
		path->value = old_pwd;
	}
	return (0);
}
