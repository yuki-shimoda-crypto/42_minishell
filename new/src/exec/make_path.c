/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:03:54 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/12 10:18:18 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char	*find_env_path(char **envp)
{
	size_t	i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (strncmp("PATH=", envp[i], 5) == 0)
		{
			path = strdup(&envp[i][5]);
			if (!path)
				assert_error("strdup\n");
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*make_absolute_path(t_node *node)
{
	char	*pathname;

	pathname = strdup(node->token->word);
	if (!pathname)
		assert_error("strdup\n");
	if (!is_file(pathname))
		file_exec_error(node->token->word, ": is a directory\n");
	else if (!is_file_exist(pathname))
		file_exec_error(node->token->word, ": no such file or directory\n");
	else if (!is_file_executable(pathname))
		file_exec_error(node->token->word, ": is not executable\n");
	return (pathname);
}

char	*make_relative_path(t_node *node, char **envp)
{
	char	*head;
	char	*tail;
	char	*env_path;
	char	*env_path_head;
	char	*pathname;
	char	*tmp;

	env_path = find_env_path(envp);
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
		tmp = strjoin_three(pathname, "/", node->token->word);
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
	if (!is_file(pathname))
		file_exec_error(node->token->word, ": is a directory\n");
	else if (!is_file_exist(pathname))
		file_exec_error(node->token->word, ": command not found\n");
	else if (!is_file_executable(pathname))
		file_exec_error(node->token->word, ": is not executable\n");
	return (pathname);
}

char	*make_pathname(t_node *node, char **envp)
{
	char	*pathname;

	if (!node->token || !node->token->word)
		return (NULL);
	if (node->token->word[0] == '/')
		pathname = make_absolute_path(node);
	else
		pathname = make_relative_path(node, envp);
	return (pathname);
}
