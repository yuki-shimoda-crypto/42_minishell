/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jikken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:51:43 by enogaWa           #+#    #+#             */
/*   Updated: 2023/02/18 15:11:15 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <sys/types.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/wait.h>


// int main()
// {
// 	pid_t	pid;
// 	int		fd[2];
// 	int		state_lock;

// 	pipe(fd);
// 	pid = fork();
// 	if (pid == 0)
// 		printf("child\n");
// 	else
// 	{
// 		wait(&state_lock);
// 		printf("parent\n");
// 	}
// 	return (0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main()
{
	int		fd[2];
	pid_t	pid;
	char	*ls_args[] = {"ls", NULL};
	char	*cat_args[] = {"cat", NULL};

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
		close(fd[1]);
		execve("/bin/ls", ls_args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
		close(fd[1]);
		execve("/bin/cat", cat_args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}
