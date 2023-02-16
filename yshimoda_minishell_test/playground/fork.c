/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 01:32:30 by yshimoda          #+#    #+#             */
/*   Updated: 2023/02/16 23:36:33 by yshimoda         ###   ########.fr       */
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


#include "playground.h"
#include <sys/wait.h>

void	pr_exit(int status)
{
	if (WIFEXITED(status))
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d%s\n", WEXITSTATUS(status),
	#ifdef	WCOREDUMP WCOREDUMP(status) ? " (core file generated)" : "");
	#else
				")";
	#endif
		else if (WIFSTOPPED(status))
			printf("child stopped, signal number = %d\n", WSTOPPED(status));
}

void
pr_exit(int status)
{
if (WIFEXITED(status))
printf("normal termination, exit status = %d\n",
WEXITSTATUS(status));
else if (WIFSIGNALED(status))
printf("abnormal termination, signal number = %d%s\n",
WTERMSIG(status),
#ifdef WCOREDUMP
8.6 関数 wait と waitpid 229
WCOREDUMP(status) ? " (core file generated)" : "");
#else
"");
#endif
else if (WIFSTOPPED(status))
printf("child stopped, signal number = %d\n",
WSTOPSIG(status));
}


int main(void)
{
	pid_t		pid;
	int			status;

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
		exit(7);

	if (wait(&status) != pid)
		err_sys("wait error");
	pr_exit(status);
	
	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
		abort();

	if (wait(&status) != pid)
		err_sys("wait error");
	pr_exit(status);

	if ((pid = fork()) < 0)
	err_sys("fork error");
	else if (pid == 0)
		status /= 0;
	
	if (wait(&status) != pid)
		err_sys("wait error");
	pr_exit(status);
	exit (0);
}

// abort(); /* SIGABRT を生成 */
// if (wait(&status) != pid) /* 子を待つ */
// err_sys("wait error");
// pr_exit(status); /* その状態を表示 */
// 
// if ((pid = fork()) < 0)qpwoalskzmxn5@gmail.com
// 230 8 プロセスの制御
// err_sys("fork error");
// else if (pid == 0) /* 子側 */
// status /= 0; /* ゼロ除算で SIGFPE を生成 */
// if (wait(&status) != pid) /* 子を待つ */
// err_sys("wait error");
// pr_exit(status); /* その状態を表示 */
// exit(0);
// }
// 
// 







































