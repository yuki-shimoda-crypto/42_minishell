/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:48:14 by yshimoda          #+#    #+#             */
/*   Updated: 2023/02/21 1 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define PATH_MAX 100

char	*search_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;

	value = getenv("PATH");
//	if (!value)
//		fatal_error("not path");
	while (*value)
	{
		bzero(path, PATH_MAX);
		end = strchr(value, ':');
		if (end)
			strncpy(path, value, end - value);
		else
			strlcpy(path, value, PATH_MAX);
		strlcat(path, "/", PATH_MAX);
		strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			char	*dup;

			dup = strdup(path);
			if (!dup)
				fatal_error("strdup");
			return (dup);
		}
		if (!end)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

void	validate_access(const char *path, const char *filename)
{
	if (!path)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
}

int	exec_cmd(t_node *node)
{
	extern char	**environ;
	char		*path;
	pid_t		pid;
	int			wstatus;
	char		**argv;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		argv = token_list_to_argv(node->args);
		path = argv[0];
		if (strchr(path, '/') == NULL)
			path = search_path(path);
		validate_access(path, argv[0]);
		execve(path, argv, environ);
		fatal_error("execve");
	}
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
	return (0);
}

int	exec(t_node *node)
{
	int		status;
	
	open_redir_file(node->redirects);
	do_redirect(node->redirects);
	status = exec_cmd(node);
	reset_redirect(node->redirects);
	return (status);
}

void	interpret(char *line, int *stat_loc)
{
	t_token	*tok;
	t_node	*node;

	tok = tokenize(line);
	if (at_eof(tok))
		;
	else if (syntax_error)
		*stat_loc = ERROR_TOKENIZE;
	else
	{
		node = parse(tok);
		if (syntax_error)
			*stat_loc = ERROR_PARSE;
		else
		{
			expand(node);
			*stat_loc = exec(node);
		}
		free_node(node);
	}
	free_tok(tok);
}

int main(void)
{
	int		status;
	char	*line;

	rl_outstream = stderr;
	status = 0;
	while(1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		interpret(line, &status);
		free(line);
	}
	exit(status);
}

//#include "playground.h"
//#include <sys/wait.h>

//void	pr_exit(int status)
//{
//	if (WIFEXITED(status))
//		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
//	else if (WIFSIGNALED(status))
//		printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
//	#ifdef WCOREDUMP
//		WCOREDUMP(status) ? " (core file generated)" : "");
//	#else
//		"");
//	#endif
//	else if (WIFSTOPPED(status))
//		printf("child stopped, signal number = %d\n", WSTOPSIG(status));
//}
//
//
