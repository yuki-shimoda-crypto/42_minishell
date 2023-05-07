/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:03:54 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 14:15:41 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <sys/stat.h>

void	check_abs_path_error(char *pathname, char *word)
{
	if (is_only_slash(pathname) || is_directory(pathname))
	{
		file_exec_error(word, ": is a directory\n");
		g_return_error.return_value = 126;
	}
	else if (!is_file(pathname) || !is_file_exist(pathname))
	{
		file_exec_error(word, ": No such file or directory\n");
		g_return_error.return_value = 127;
	}
	else if (!is_file_executable(pathname))
	{
		file_exec_error(word, ": Permission deied\n");
		g_return_error.return_value = 126;
	}	
}

char	*make_absolute_path(t_tk *token)
{
	char	*pathname;
	char	*split;
	char	*path;

	pathname = ft_strdup(token->word);
	path = token->word;
	path++;
	while (ft_strchr(path, '/'))
	{
		split = ft_strndup(path, (path - ft_strchr(path, '/')));
		path = ft_strchr(path, '/');
		path++;
		if (check_file_dir_error(split, path, token))
		{
			free(split);
			return (pathname);
		}
		free(split);
	}
	if (!pathname)
		assert_error("strdup\n");
	check_abs_path_error(pathname, token->word);
	return (pathname);
}

char	*make_relative_path(const char *word)
{
	char	*pathname;
	char	*abs_path;
	char	*tmp;

	pathname = NULL;
	abs_path = wrap_getcwd(NULL, 0);
	if (!abs_path)
		assert_error("get_cwd\n");
	while (is_relative_path(word))
	{
		if (!ft_strncmp(word, "./", 2))
			word += 2;
		else if (!ft_strncmp(word, "../", 3))
		{
			word += 3;
			tmp = ft_strrchr(abs_path, '/');
			if (tmp)
				*tmp = '\0';
		}
	}
	return (check_pathname_error(pathname, abs_path, word));
}

char	*make_environment_path(t_tk *token, t_env *env_list)
{
	char	*head;
	char	*tail;
	char	*env_path;
	char	*env_path_head;
	char	*pathname;

	pathname = NULL;
	env_path = find_env_path(env_list);
	env_path_head = env_path;
	while (env_path && *env_path)
	{
		head = env_path;
		tail = ft_strchr(env_path, ':');
		pathname = get_pathname(head, tail, &token->word);
		if (is_file_exist(pathname) && is_file_executable(pathname))
			break ;
		if (tail == NULL)
			break ;
		free(pathname);
		env_path = tail + 1;
	}
	free(env_path_head);
	check_error_env_path(pathname, token->word);
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
	else if (is_relative_path(token->word))
		pathname = make_relative_path(token->word);
	else if (is_dot(token->word))
	{
		file_exec_error(token->word, ": command not found\n");
		g_return_error.return_value = 127;
		return (NULL);
	}
	else
		pathname = make_environment_path(token, env_list);
	return (pathname);
}
