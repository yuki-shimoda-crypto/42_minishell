/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:03:54 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/06 14:36:37 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <sys/stat.h>

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

bool	is_directory(const char *pathname)
{
	struct stat st;

	if (stat(pathname, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (true);
	}
	return (false);
}

char	*make_absolute_path(t_tk *token)
{
	char	*pathname;
	char	*split;
	char	*path;

	pathname = strdup(token->word);
	path = token->word;
	path++;
	while (strchr(path, '/'))
	{
		split = strndup(path, (path - strchr(path, '/')));
		path = strchr(path, '/');
		path++;
		if (!is_directory(split) && is_file(split))
		{
			if (strchr(path, '/'))
			{
				file_exec_error(token->word, ": Not a directory\n");
				g_return_error.return_value = 126;
				free(split);
				return (pathname);
			}
		}
		free(split);
	}
	if (!pathname)
		assert_error("strdup\n");
	if (is_only_slash(pathname) || is_directory(pathname))
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
		if (!strncmp(word, "./", 2))
			word += 2;
		else if (!strncmp(word, "../", 3))
		{
			word += 3;
			tmp = strrchr(abs_path, '/');
			if (tmp)
				*tmp = '\0';
		}
	}
	pathname = strjoin(abs_path, word - 1);
	free(abs_path);
	if (!pathname)
		assert_error("malloc\n");
	if (*(word) == '\0')
	{
		file_exec_error(word, ": Permission deied\n");
		g_return_error.return_value = 126;
	}
	else if (!is_file_exist(pathname))
	{
		file_exec_error(word, ": No such file or directory\n");
		g_return_error.return_value = 127;
	}
	else if (!is_file_executable(pathname) || pathname[0] == '\0')
	{
		file_exec_error(word, ": Permission deied\n");
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
		{
			pathname = strndup(head, tail - head);
			if (!*(tail + 1))
				tail = NULL;
		}
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

bool	is_relative_path(const char *word)
{
	size_t	len;

	len = strlen(word);
	if (2 <= len && !strncmp(word, "./", 2))
		return (true);
	if (3 <= len && !strncmp(word, "../", 3))
		return (true);
	return (false);
}

bool	is_dot(const char *word)
{
	size_t	len;

	len = strlen(word);
	if (len == 1 && !strncmp(word, ".", 1))
		return (true);
	else if (len == 2 && !strncmp(word, "..", 2))
		return (true);
	return (false);
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
		g_return_error.exec_error = true;
		g_return_error.return_value = 127;
		return (NULL);
	}
	else
		pathname = make_environment_path(token, env_list);
	return (pathname);
}
