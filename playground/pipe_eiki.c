#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void	main(int argc, char **argv, char *envp[])
{
	int	pipe_fd[2];
	int	pipe_fd2[2];
	pid_t	pid;
	pid_t	pid2;
	pid_t	pid3;
	char	buf[100];
	int		bufsize = 100;
	int		wstatus;
	int		num_read;
	char	*exec1[] = {"ls", NULL};
	char	*exec2[] = {"wc", "-l", NULL};
	char	*exec3[] = {"wc", NULL};

	if (pipe(pipe_fd) == -1)
	{
		write (2, "pipe error\n", strlen("pipe error\n"));
		exit (1);
	}
	if (pipe(pipe_fd2) == -1)
	{
		write (2, "pipe error\n", strlen("pipe error\n"));
		exit (1);
	}

	pid = fork();
	if (pid == -1)
	{
		write (2, "fork error\n", strlen("fork error\n"));
		exit (1);
	}
	else if (pid == 0)
	{
		
		close(pipe_fd2[0]);//
		close(pipe_fd2[1]);//
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			write (2, "dup2 error\n", strlen("dup2 error\n"));
			exit (1);
		}
		close(pipe_fd[1]);
		execve("/bin/ls", exec1, envp);
	}
	else
		;
	pid2 = fork();
	if (pid2 == -1)
	{
		write (2, "fork error\n", strlen("fork error\n"));
		exit (1);
	}
	else if (pid2 == 0)
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			write (2, "dup2 error\n", strlen("dup2 error\n"));
			exit (1);
		}
		close(pipe_fd[0]);
		close(pipe_fd2[0]);
		if (dup2(pipe_fd2[1], STDOUT_FILENO) == -1)
		{
			write (2, "dup2 error\n", strlen("dup2 error\n"));
			exit (1);
		}
		close(pipe_fd2[1]);
		execve("/bin/wc", exec2, envp);
		write (2, "exec error\n", strlen("exec error\n"));
	}
	else
		;
	pid3 = fork();
	if (pid3 == -1)
	{
		write (2, "fork error\n", strlen("fork error\n"));
		exit (1);
	}
	else if (pid3 == 0)
	{
		close(pipe_fd[0]);//
		close(pipe_fd[1]);//
		close(pipe_fd2[1]);
		if (dup2(pipe_fd2[0], STDIN_FILENO) == -1)
		{
			write (2, "dup2 error\n", strlen("dup2 error\n"));
			exit (1);
		}
		close(pipe_fd2[0]);
		execve("/bin/wc", exec3, envp);
	}
	else
		;
	if (close(pipe_fd[0]) == -1)
	{
		write (2, "dup2 error\n", strlen("dup2 error\n"));
		exit (1);
	}
	if (close(pipe_fd[1]) == -1)
	{
		write (2, "dup2 error\n", strlen("dup2 error\n"));
		exit (1);
	}
	if (close(pipe_fd2[0]) == -1)
	{
		write (2, "dup2 error\n", strlen("dup2 error\n"));
		exit (1);
	}
	if (close(pipe_fd2[1]) == -1)
	{
		write (2, "dup2 error\n", strlen("dup2 error\n"));
		exit (1);
	}
	if (wait(NULL) == -1)
	{
		write (2, "dup2 error\n", strlen("dup2 error\n"));
		exit (1);
	}
	if (wait(NULL) == -1)
	{
		write (2, "dup2 error\n", strlen("dup2 error\n"));
		exit (1);
	}
	if (wait(NULL) == -1)
	{
		write (2, "dup2 error\n", strlen("dup2 error\n"));
		exit (1);
	}
}