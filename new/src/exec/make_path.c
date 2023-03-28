/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:03:54 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/28 14:21:18 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char	*find_env_path(t_env *env_list)
{
	char	*value;

	while (env_list)
	{
		if (!strcmp("PATH", env_list->key))
		{
			value = strdup(env_list->value);
			if (!value)
				assert_error("strdup\n");
			return (value);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

bool	is_only_slash(const char *pathname)
{
	size_t	i;

	if (!pathname || !*pathname)
		return (false);
	i = 0;
	while (pathname[i])
	{
		if (pathname[i] != '/')
			return (false);
		i++;
	}
	return (true);
}

char	*make_absolute_path(t_tk *token)
{
	char	*pathname;

	pathname = strdup(token->word);
	if (!pathname)
		assert_error("strdup\n");
	if (is_only_slash(pathname))
	{
		file_exec_error(token->word, ": is a directory\n");
		g_return_error.return_value = 126;
	}
	else if (!is_file(pathname) || !is_file_exist(pathname))
	{
		file_exec_error(token->word, ": No such file or directory\n");
		g_return_error.return_value = 127;
	}
	else if (!is_file_executable(pathname))
	{
		file_exec_error(token->word, ": Permission deied\n");
		g_return_error.return_value = 126;
	}
	return (pathname);
}

char	*make_environment_path(t_tk *token, t_env *env_list)
{
	char	*head;
	char	*tail;
	char	*env_path;
	char	*env_path_head;
	char	*pathname;
	char	*tmp;

	pathname = NULL;
	env_path = find_env_path(env_list);
	env_path_head = env_path;
	while (env_path && *env_path)
	{
		head = env_path;
		tail = strchr(env_path, ':');
		if (tail)
			pathname = strndup(head, tail - head);
		else
			pathname = strdup(head);
		if (!pathname)
			assert_error("strndup\n");
		tmp = strjoin_three(pathname, "/", token->word);
		free(pathname);
		if (!tmp)
			assert_error("malloc\n");
		pathname = tmp;
		if (is_file_exist(pathname) && is_file_executable(pathname))
			break ;
		if (tail == NULL)
			break ;
		free(pathname);
		env_path = tail + 1;
	}
	free(env_path_head);
	if (!pathname || !is_file(pathname))
	{
		file_exec_error(token->word, ": No such file or directory\n");
		g_return_error.return_value = 127;
	}
	else if (!is_file_exist(pathname))
	{
		file_exec_error(token->word, ": command not found\n");
		g_return_error.return_value = 127;
	}
	else if (!is_file_executable(pathname))
	{
		file_exec_error(token->word, ": Permission deied\n");
		g_return_error.return_value = 126;
	}
	return (pathname);
}

char	*make_pathname(t_tk *token, t_env *env_list)
{
	char	*pathname;

	if (!token || !token->word)
		return (NULL);
	if (is_builtin(token->word))
		return (NULL);
	if (token->word[0] == '/')
		pathname = make_absolute_path(token);
//	else if (token->word[0] == '.')
//		pathname = 
	else
		pathname = make_environment_path(token, env_list);
	return (pathname);
}
