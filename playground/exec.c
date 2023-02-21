/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 09:47:13 by yshimoda          #+#    #+#             */
/*   Updated: 2023/02/18 11:50:23 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "playground.h"

char	*env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
	{
		if (execle("/goinfre/yshimoda/minishell/yshimoda_minishell_test/playground/echoall", "echoall", "myarg1", "MY ARG2", (char *)0, env_init) < 0)
			err_sys("execle error");
	}
	
	if ((waitpid(pid, NULL, 0)) < 0)
		err_sys("wait error");
	
	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
	{
		if (execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0)
			err_sys("execlp error");
	}
	exit(0);
}

// echoall source

//int main(int argc, char const *argv[])
//{
//	int			i;
//	char		**ptr;
//	extern char	**environ;
//
//	for (int i = 0; i < argc; i++)
//		printf("argv[%d]: %s\n", i, argv[i]);
//	
//	for (ptr = environ; *ptr != 0; ptr++)
//		printf("%s\n", *ptr);
//	exit (0);
//}
