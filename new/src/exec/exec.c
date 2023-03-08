/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 04:15:24 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/08 17:13:220 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

char	*strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	char	*save;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (strdup(s2));
	if (!s2)
		return (strdup(s1));
	ptr = (char *)malloc(strlen(s1) + strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	save = ptr;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = 0;
	return (save);
}


bool	is_file_executable(char *pathname)
{
	if (!access(pathname, X_OK))
		return (true);
	return (false);
}

bool	is_file_exist(char *pathname)
{
	if (!access(pathname, F_OK))
		return (true);
	return (false);
}

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
				assert_error("strdup");
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
	if (!is_file_exist(pathname))
		file_exec_error(node->token->word, ": is not exist\n");
	else if (!is_file_executable(pathname))
		file_exec_error(node->token->word, ": is not executable\n");
	return (pathname);
}


char	*make_relative_path(t_node *node, char **envp)
{
	char	*head;
	char	*tail;
	char	*env_path;
	char	*pathname;
	char	*tmp;

	env_path = find_env_path(envp);
	while (env_path && *env_path)
	{
		head = env_path;
		tail = strchr(env_path, ':');
		if (!tail)
			pathname = strndup(head, tail - head);
		else
			pathname = strdup(head);
		if (!pathname)
			assert_error("strndup\n");
		tmp = strjoin(pathname, node->token->word);
		free(pathname);
		pathname = tmp;
		if (is_file_exist(pathname) && is_file_executable(pathname))
			break ;
		env_path = tail + 1;
	}
	free(env_path);
	if (!is_file_exist(pathname))
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

size_t	argv_len(t_tk *token)
{
	size_t	len;

	len = 0;
	while (token)
	{
		len++;
		token = token->next;
	}
	return (len);
}


char	**make_argv(t_node *node)
{
	size_t	i;
	size_t	len;
	char	**argv;
	t_tk	*token;

	if (!node->token)
		return (NULL);
	i = 0;
	len = argv_len(node->token);
	argv = malloc(sizeof(char *) * (len + 1));
	token = node->token;
	while (token->kind != TK_EOF)
	{
		argv[i] = strdup(node->token->word);
		if (!argv[i])
			assert_error("strdup");
		token = token->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

void	exec(char *pathname, char **argv, char **envp)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
		assert_error("fork");
	else if (pid == 0)
	{
		execve(pathname, argv, envp);
		assert_error("execve");
	}
	else
	{
		wait(&wstatus);
		(void)wstatus;
	}
}

// bool	is_builtin(char **argv)
// {
// 	if (strncmp("cd", argv[0], 2))
// 		cd();
// 	else if (strncmp("echo", argv[0], 4))
// 		echo();
// 	else if (strncmp("env", argv[0], 3))
// 		env();
// 	else if (strncmp("exit", argv[0], 4))
// 		exit();
// 	else if (strncmp("export", argv[0], 6))
// 		export();
// 	else if (strncmp("pwd", argv[0], 3))
// 		pwd();
// 	else if (strncmp("unset", argv[0], 5))
// 		unset();
// 	else
// 		return (false);
// 	return (true);
	
// }

// int	open_redir_file(t_node *redir)
// {
// 	int	fd;

// 	if (redir->kind == ND_REDIRECT_OUT)
// 		fd = open (redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	else if (redir->kind == ND_REDIRECT_APPEND)
// 		fd = open (redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	else if (redir->kind == ND_REDIRECT_IN)
// 		fd = open (redir->filename, O_RDONLY);
// 	else if (redir->kind == ND_REDIRECT_HEREDOC)
// 		return (heredoc);
// 	return (fd);
// }

// void	redirect_fd_list(t_node *node)
// {
// 	t_node	*redir;

// 	redir = node->redirect;
// 	while (redir->filename)
// 	{
// 		redir->filefd = open_redir_file(redir);
// 		redir = redir->redirect;
// 	}
// }

// void	do_redirect(t_node *node)
// {
// 	t_node	*redir;
// 	int		old_fd;

// 	redir = node;
// 	while (1)
// 	{
		
// 	}
// }

void	exec_cmd(t_node *node, char **envp)
{
	char	*pathname;
	char	**argv;

//	redirect_fd_list();
//	do_redirect();
	while (node)
	{
		pathname = make_pathname(node, envp);
		argv = make_argv(node);
		node = node->pipe;
		if (g_return_error.exec_error)
			continue ;
		// argv = NULL;
		// if (is_builtin(argv))
		// 	exec_builtin();
		// else
		// printf("%s\n", pathname);
		// printf("%p\n", pathname);
		// for (int i = 0; argv[i]; i++)
			// printf("%s\n", argv[i]);
		// printf("%p\n", argv);
		exec(pathname, argv, envp);
	}
}
