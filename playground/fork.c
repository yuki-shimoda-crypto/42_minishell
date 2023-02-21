/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 01:32:30 by yshimoda          #+#    #+#             */
/*   Updated: 2023/02/18 09:05:06 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "playground.h"

// int main (void)
// {
// 	char	buf[MAXLINE];
// 	pid_t	pid;
// 	int		status;
// 
// 	printf("%%");
// 	while (fgets(buf, MAXLINE, stdin) != NULL)
// 	{
// 		if (buf[strlen(buf) - 1] == '\n')
// 			buf[strlen(buf) - 1] = '0';
// 
// 		if ((pid = fork()) < 0)
// 			err_sys("fork error");
// 		else if (pid == 0)
// 		{
// 			execlp(buf, buf, (char *)0);
// 			err_ret("couldn't execute: %s", buf);
// 			exit(127);
// 		}
// 
// 		if ((pid = waitpid(pid, &status, 0)) < 0)
// 			err_sys("waitpid error");
// 		printf("%%");
// 	}
// }
// 

// #include <stdio.h>
// 
// int			globvar = 6;
// char		buf[] = "a write to stdout\n";
//
// int main(void)
// {
// 	int		var;
// 	pid_t	pid;
// 
// 	var = 88;
// 	if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
// 		err_sys("write error");
// 	printf("before fork\n");
// 	if (pid == fork() < 0)
// 		err_sys("fork error");
// 	else if (pid == 0)
// 	{
// 		globvar++;
// 		var++;
// 	}
// 	else
// 		sleep(2);
// 	printf("pid = %ld, glog = %d, var = %d\n", (long)getpid(), globvar, var);
// 	exit(0);
// }
// 

// #include "playground.h"
// 
// int main(void)
// {
// 	int		var;
// 	pid_t	pid;
// 
// 	var = 88;
// 	printf("before vfork\n");
// 	if ((pid = vfork()) < 0)
// 		err_sys("vfork error");
// 	else if (pid == 0)
// 	{
// 		globvar++;
// 		var++;
// 		_exit(0);
// 	}
// 	printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
// 	exit (0);
// }

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
//int main(void)
//{
//	pid_t		pid;
//	int			status;
//
//	if ((pid = fork()) < 0)
//		err_sys("fork error");
//	else if (pid == 0)
//		exit(7);
//
//	if (wait(&status) != pid)
//		err_sys("wait error");
//	pr_exit(status);
//	
//	if ((pid = fork()) < 0)
//		err_sys("fork error");
//	else if (pid == 0)
//		abort();
//
//	if (wait(&status) != pid)
//		err_sys("wait error");
//	pr_exit(status);
//
//	if ((pid = fork()) < 0)
//	err_sys("fork error");
//	else if (pid == 0)
//		status /= 0;
//	
//	if (wait(&status) != pid)
//		err_sys("wait error");
//	pr_exit(status);
//	exit (0);
//}



// #include "playground.h"
// #include <sys/wait.h>
// 
// int main(void)
// {
// 	pid_t		pid;
// 
// 	if ((pid = fork()) < 0)
// 		err_sys("fork error");
// 	else if (pid == 0)
// 	{
// 		if ((pid = fork()) < 0)
// 			err_sys("fork error");
// 		else if (pid > 0)
// 			exit(0);
// 
// 		sleep(2);
// 		printf("second child, parent pid = %ld\n", (long)getppid());
// 		exit(0);
// 	}
// 
// 	if (waitpid(pid, NULL, 0) != pid)
// 		err_sys("waitpid error");
// 
// 	exit(0);
// }

#include "playground.h"

static void charatatime (char *);

int	main(void)
{
	pid_t		pid;

	TELL_WAIT();

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
	{
		//WAIT_PARENT();
		charatatime("output from child\n");
		TELL_PARENT(getppid());
	}
	else
	{
		WAIT_CHILD();
		charatatime("output from parent\n");
		//TELL_CHILD(pid);
	}
	exit (0);
}

static void	charatatime(char *str)
{
	char	*ptr;
	int		c;

	setbuf(stdout, NULL);
	for (ptr = str; (c = *ptr++) != 0; )
		putc(c, stdout);
}








































