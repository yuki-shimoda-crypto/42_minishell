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

char	*strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*ptr;
	char	*save;

	if (!s1 || !s2 || !s3)
		return (NULL);
	ptr = (char *)malloc(strlen(s1) + strlen(s2) + strlen(s3) + 1);
	if (!ptr)
		return (NULL);
	save = ptr;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	while (*s3)
		*ptr++ = *s3++;
	*ptr = 0;
	return (save);
}

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

char	**make_argv(t_tk *token)
{
	size_t	i;
	size_t	len;
	char	**argv;

	if (!token)
		return (NULL);
	i = 0;
	len = argv_len(token);
	argv = calloc(len + 1, sizeof(char *));
	if (!argv)
		assert_error("malloc\n");
	while (token->kind != TK_EOF)
	{
		argv[i] = strdup(token->word);
		if (!argv[i])
			assert_error("strdup\n");
		token = token->next;
		i++;
	}
	return (argv);
}

void	exec(char *pathname, char **argv, char **envp)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
		assert_error("fork\n");
	else if (pid == 0)
	{
		execve(pathname, argv, envp);
		assert_error("execve\n");
	}
	else
	{
		wait(&wstatus);
		(void)wstatus;
	}
}

void	free_argv(char **argv)
{
	size_t	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
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

void	exec_cmd(t_node *node, char **envp)
{
	char	*pathname;
	char	**argv;

	while (node)
	{
		pathname = make_pathname(node, envp);
		argv = make_argv(node->token);
		redirect_fd_list(node->redirect);
		do_redirect(node->redirect);
		if (g_return_error.exec_error)
		{
			free(pathname);
			free_argv(argv);
			node = node->pipe;
			continue ;
		}
		// if (is_builtin(argv))
		// 	exec_builtin();
		// else
		exec(pathname, argv, envp);
		reset_redirect(node->redirect);
		node = node->pipe;
		free(pathname);
		free_argv(argv);
	}
}