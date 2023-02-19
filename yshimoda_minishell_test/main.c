/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:48:14 by yshimoda          #+#    #+#             */
/*   Updated: 2023/02/19 16:58:07 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fatal_error(const char *msg) __attribute__((noreturn));

void	validate_access(const char *path, const char *filename)
{
	if (!path)
		err
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

int	exec(char *argv[])
{
	extern char	**environ;
	const char	*path = argv[0];
	pid_t		pid;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		if (strchr(path, '/') == NULL)
			path = search_path(path);
	}
	else
		
}


void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

int	interpret(char *line)
{
	extern char **environ;
	char		*argv[] = {line, NULL};
	pid_t		pid;
	int			wstatus;

	if ((pid = fork()) < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		execve(line, argv, environ);
		fatal_error("execve");
	}
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
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
