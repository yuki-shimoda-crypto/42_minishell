/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:48:14 by yshimoda          #+#    #+#             */
/*   Updated: 2023/02/18 13:07:11 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fatal_error(const char *msg) __attribute__((noreturn));

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
//`