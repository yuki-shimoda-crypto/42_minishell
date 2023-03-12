/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:04:57 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/12 13:11:47 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define BUF_SIZE 10

// int main(int argc, char *argv[])
// {
// 	int		filedes[2];
// 	char	buf[BUF_SIZE];
// 	pid_t	pid;
// 	int		num_read;
// 
// 	if (argc != 2 || strcmp(argv[1], "--help") == 0)
// 	{
// 		printf("Usage Error\n");
// 		printf("%s string\n", argv[0]);
// 		return (1);
// 	}
// 	if (pipe(filedes) == -1)
// 	{
// 		printf("%s\n", "Error, pipe");
// 		exit(1);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		printf("%s\n", "Error, fork");
// 		exit(1);
// 	}
// 	else if (pid == 0)
// 	{
// 		if (close(filedes[1]) == -1)
// 		{
// 			printf("%s\n", "Error, close");
// 			exit(1);
// 		}
// 		while (1)
// 		{
// 			num_read = read(filedes[0], buf, BUF_SIZE);
// 			if (num_read == -1)
// 			{
// 				printf("%s\n", "Error read\n");
// 				exit(1);
// 			}
// 			if (num_read == 0)
// 				break ;
// 			if (write(STDOUT_FILENO, buf, num_read) != num_read)
// 			{
// 				printf("%s\n", "Error write\n");
// 				exit(1);
// 			}
// 		}
// 		write(STDOUT_FILENO, "\n", 1);
// 		if (close(filedes[0]) == -1)
// 		{
// 			printf("%s\n", "Error close\n");
// 			exit(1);
// 		}
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		if (close(filedes[0]) == -1)
// 		{
// 			printf("%s\n", "Error, close");
// 			exit(1);
// 		}
// 		write(filedes[1], argv[1], strlen(argv[1]));
// 		close(filedes[1]);
// 		wait(NULL);
// 		exit(EXIT_SUCCESS);
// 	}
// 	return (0);
// }

void	assert_error(const char *msg)
{
	write(STDERR_FILENO, "assert errro\n", strlen("assert errro\n"));
	if (msg)
		write(STDERR_FILENO, msg, strlen(msg));
	exit(1);
}

#include <stdio.h>

int main(int argc)
{
	int		pipefd_1[2];
	int		pid_1;
	int		pid_2;
	char	*argv_1[] = {"ls", NULL};
	char	*argv_2[] = {"wc", "-l", NULL};
	extern char **environ;

	if (pipe(pipefd_1) == -1)
		assert_error("pipe\n");

	// process 1
	pid_1 = fork();
	if (pid_1 == -1)
		assert_error("fork\n");
	else if (pid_1 == 0)
	{
		if (close(pipefd_1[0]) == -1)
			assert_error("close\n");
		if (pipefd_1[1] != STDOUT_FILENO)
		{
			if (dup2(pipefd_1[1], STDOUT_FILENO) == -1)
				assert_error("dup2\n");
			if (close(pipefd_1[1]) == -1)
				assert_error("close\n");
		}
		execve("/bin/ls", argv_1, environ);
		assert_error("execve\n");
	}
	else
		;
	
	// process 2
	pid_2 = fork();
	if (pid_2 == -1)
		assert_error("fork\n");
	else if (pid_2 == 0)
	{
		if (close(pipefd_1[1]) == -1)
			assert_error("close\n");
		if (pipefd_1[0] != STDIN_FILENO)
		{
			if (dup2(pipefd_1[0], STDIN_FILENO) == -1)
				assert_error("dup2\n");
			if (close(pipefd_1[0]) == -1)
				assert_error("close\n");
		}
		execve("/bin/wc", argv_2, environ);
		assert_error("execve\n");
	}
	else
		;

	if (close(pipefd_1[0]) == -1)
		assert_error("close\n");
	if (close(pipefd_1[1]) == -1)
		assert_error("close\n");
	if (wait(NULL) == -1)
		assert_error("wait\n");
	if (wait(NULL) == -1)
		assert_error("wait\n");
	return (0);
}
