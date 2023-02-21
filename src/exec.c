/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:05:23 by enogaWa           #+#    #+#             */
/*   Updated: 2023/02/18 16:30:17 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	token_num(t_token_list	*tk_list)
// {
// 	int				i;
// 	t_token_list	*tmp;

// 	i = 0;
// 	tmp = tk_list;
// 	while (tmp->kind == TK_WORD)
// 	{
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	return (i);
// }

void	exe(t_token_list *tk_list)
{
	char	**exec;
	pid_t	pid;
	int		wstatus;

	exec = malloc(sizeof(char *) * 2);
	exec[0] = ft_strdup(tk_list->token);
	tk_list = tk_list->next;
	while (tk_list->kind == TK_WORD)
	{
		exec[1] = ft_strjoin(exec[1], tk_list->token);
		exec[1] = ft_strjoin(exec[1], " ");
		tk_list = tk_list->next;
	}
	// exec[1] = ft_strjoin(exec[1], "\0");
	// exec[2] = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		execve(ft_strjoin("/bin/", exec[0]), exec, NULL);
	else
		wait(&wstatus);
}
