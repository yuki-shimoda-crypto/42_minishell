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
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>

static size_t	get_size(int n)
{
	size_t	len;

	len = 0;
	if (!n)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*itoa(int n)
{
	char	*s;
	size_t	len;
	int		num;

	len = get_size(n);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s[len] = '\0';
	num = n;
	while (len--)
	{
		if (num < 0)
			s[len] = -(num % 10) + '0';
		else
			s[len] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		*s = '-';
	return (s);
}

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

void	exec(char *pathname, char **argv, char **envp, t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		assert_error("fork\n");
	else if (pid == 0)
	{
		connect_pipe(node);
		execve(pathname, argv, envp);
		assert_error("execve\n");
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
	free(argv);
}

void	free_envp(char **envp)
{
	size_t	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

bool	is_builtin(const char *cmd)
{
	if (!cmd)
		return (false);
	if (!strcmp("cd", cmd))
		return (true);
	else if (!strcmp("echo", cmd))
		return (true);
	else if (!strcmp("env", cmd))
		return (true);
	else if (!strcmp("exit", cmd))
		return (true);
	else if (!strcmp("export", cmd))
		return (true);
	else if (!strcmp("pwd", cmd))
		return (true);
	else if (!strcmp("unset", cmd))
		return (true);
	else
		return (false);
}

size_t	count_pipe_num(t_node *node)
{
	size_t	num;

	num = 0;
	while (node)
	{
		node = node->pipe;
		num++;
	}
	return (num);
}

size_t	env_list_size(t_env *env_list)
{
	size_t		i;

	i = 0;
	while (env_list)
	{
		env_list = env_list->next;
		i++;
	}
	return (i);
}

char	**make_envp(t_env *env_list)
{
	char	**envp;
	size_t	list_size;
	size_t	i;

	list_size = env_list_size(env_list);
	envp = calloc(list_size + 1, sizeof(char *));
	if (!envp)
		assert_error("calloc\n");
	i = 0;
	while (i < list_size)
	{
		envp[i] = strjoin_three(env_list->key, "=", env_list->value);
		if (!envp[i])
			assert_error("strjoin_three, malloc\n");
		i++;
		env_list = env_list->next;
	}
	return (envp);
}

// void	exec_cmd(t_node *node, t_env **env_list)
// {
// 	char	*pathname;
// 	char	**argv;
// 	char	**envp;
// 	size_t	i;
// 	size_t	pipe_num;
// 
// 	pipe_num = count_pipe_num(node);
// 	input_pipefd(node, NULL);
// 	expand(node, *env_list);
// 	envp = make_envp(*env_list);
// 	while (node)
// 	{
// 		pathname = make_pathname(node->token, *env_list);
// 		argv = make_argv(node->token);
// 		redirect_fd_list(node->redirect);
// 		if (g_return_error.redirect_error)
// 		{
// 			free(pathname);
// 			free_argv(argv);
// 			node = node->pipe;
// 			g_return_error.redirect_error = false;
// 			continue ;
// 		}
// 		do_redirect(node->redirect);
// 		if (g_return_error.exec_error)
// 		{
// 			free(pathname);
// 			free_argv(argv);
// 			node = node->pipe;
// 			g_return_error.exec_error = false;
// 			continue ;
// 		}
// 		if (argv && is_builtin(argv[0]))
// 		{
// 			connect_pipe_builtin(node);
// 			recognize_builtin(argv, env_list);
// 			reset_pipe_builtin(node);
// 		}
// 		else
// 		{
// 			// connect_pipe(node);
// 			if (pathname && argv)
// 				exec(pathname, argv, envp, node);
// 		}
// 		reset_redirect(node->redirect);
// 		if (node->inpipe[0] != INT_MAX)
// 		{
// 			wrap_close(node->inpipe[1]);
// 			wrap_close(node->inpipe[0]);
// 		}
// 		node = node->pipe;
// 		free(pathname);
// 		free_argv(argv);
// 	}
// 	free_envp(envp);
// 	i = 0;
// 	while (i < pipe_num)
// 	{
// 		wait(NULL);
// 		i++;
// 	}
// }

void	wait_child_process(void)
{
	int		status;
	pid_t	pid;

	status = 0;
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1 && errno == ECHILD)
			break ;
		else if (pid == -1)
		{
			perror(NULL);
			assert_error("waitpid\n");
		}
		else if (WIFEXITED(status))
			g_return_error.return_value = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (isatty(STDIN_FILENO))
				wrap_write(STDOUT_FILENO, "\n", 1);
			g_return_error.g_sig = 0;
			if (WTERMSIG(status) == SIGINT)
				g_return_error.ctrl_c = true;//
			g_return_error.return_value = 128 + WTERMSIG(status);
		}
	}
}

void	exec_cmd(t_node *node, t_env **env_list)
{
	char	*pathname;
	char	**argv;
	char	**envp;
	pid_t	pid;

	input_pipefd(node, NULL);
	expand(node, *env_list);
	envp = make_envp(*env_list);
	while (node)
	{
		pathname = make_pathname(node->token, *env_list);
		argv = make_argv(node->token);
		if (!argv)
		{
			node = node->pipe;
			continue ;
		}
		redirect_fd_list(node->redirect, *env_list);//
		if (g_return_error.redirect_error)
		{
			free(pathname);
			free_argv(argv);
			node = node->pipe;
			g_return_error.redirect_error = false;
			continue ;
		}
		do_redirect(node->redirect);
		if (node->token->kind != TK_WORD)///
		{
			reset_redirect(node->redirect);
			free(pathname);
			free_argv(argv);
			node = node->pipe;
			continue ;
		}///
		if (g_return_error.exec_error)
		{
			free(pathname);
			free_argv(argv);
			node = node->pipe;
			g_return_error.exec_error = false;
			continue ;
		}
		if (argv && is_builtin(argv[0]))
		{
			connect_pipe_builtin(node);
			recognize_builtin(argv, env_list);
			reset_pipe_builtin(node);
		}
		else
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				// Child process
				signal(SIGQUIT, SIG_DFL);///
				signal(SIGINT, SIG_DFL);///
				connect_pipe(node);
				if (pathname && argv)
				{
					execve(pathname, argv, envp);
					perror("execve");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				// Parent process
				if (node->inpipe[0] != INT_MAX)
				{
					wrap_close(node->inpipe[1]);
					wrap_close(node->inpipe[0]);
				}
			}
		}
		reset_redirect(node->redirect);
		node = node->pipe;
		free(pathname);
		free_argv(argv);
	}
	free_envp(envp);
	wait_child_process();
}
