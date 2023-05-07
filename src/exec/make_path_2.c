/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_path_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:56:32 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 16:17:29 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pathname(char *head, char *tail, char **word)
{
	char	*pathname;
	char	*tmp;

	if (tail)
	{
		pathname = ft_strndup(head, tail - head);
		if (!*(tail + 1))
			tail = NULL;
	}
	else
		pathname = ft_strdup(head);
	if (!pathname)
		assert_error("ft_strndup\n");
	tmp = ft_strjoin_three(pathname, "/", *word);
	free(pathname);
	if (!tmp)
		assert_error("malloc\n");
	return (tmp);
}

void	check_error_env_path(char *pathname, char *word)
{
	if (!pathname || !is_file(pathname))
	{
		file_exec_error(word, ": No such file or directory\n");
		g_return_error.return_value = 127;
	}
	else if (!is_file_exist(pathname))
	{
		file_exec_error(word, ": command not found\n");
		g_return_error.return_value = 127;
	}
	else if (!is_file_executable(pathname))
	{
		file_exec_error(word, ": Permission deied\n");
		g_return_error.return_value = 126;
	}
}

char	*check_pathname_error(char *pathname, char *abs_path, const char *word)
{
	pathname = ft_strjoin(abs_path, word - 1);
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

char	*find_env_path(t_env *env_list)
{
	char	*value;

	while (env_list)
	{
		if (!ft_strcmp("PATH", env_list->key))
		{
			value = ft_strdup(env_list->value);
			if (!value)
				assert_error("ft_strdup\n");
			return (value);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

bool	check_file_dir_error(char *split, char *path, t_tk *token)
{
	if (!is_directory(split) && is_file(split))
	{
		if (ft_strchr(path, '/'))
		{
			file_exec_error(token->word, ": Not a directory\n");
			g_return_error.return_value = 126;
			return (true);
		}
	}
	return (false);
}
