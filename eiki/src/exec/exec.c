/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:05:23 by enogaWa           #+#    #+#             */
/*   Updated: 2023/02/28 15:52:01 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe(t_token_list *tk_list)
{
	char		**exec;
	extern char	**environ;
	pid_t		pid;
	int			wstatus;

	exec = make_array(tk_list);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		execve(ft_strjoin("/bin/", exec[0]), exec, environ);
	else
	{
		wait(&wstatus);
		free (exec);
		return ;
	}
}
