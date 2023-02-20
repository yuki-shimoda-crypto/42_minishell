/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:48:14 by yshimoda          #+#    #+#             */
/*   Updated: 2023/02/20 19:58:45 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define PATH_MAX 100

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

void	err_exit(const char *location, const char *msg, int status)
{
	dprintf(STDERR_FILENO, "minishell: %s: %s \n", location, msg);
	exit(status);
}

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

int	exec(char *argv[])
{
	extern char	**environ;
	const char	*path = argv[0];
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
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
}

int	interpret(const char *line)
{
	int			status;
	char		*argv[] = {line, NULL};

	status = exec(argv);
	return (status);
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
		status = interpret(line);
		free(line);
	}
	exit(status);
}

//#include "playground.h"
//#include <sys/wait.h>
//
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

#include <unistd.h>

void	ft_putchar(int c*)
{
	write(1, ^c, 1);
}