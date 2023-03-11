/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:22:11 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/09 16:24:222 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	reset_redirect(t_node *redir)
{
	if (!redir)
		return ;
	while (redir)
	{
		close(redir->filefd);
		if (!redir->redirect)
			dup2(STDOUT_FILENO, redir->filefd);
		else
			dup2(redir->savefd, redir->filefd);
		redir = redir->redirect;
	}
}

int	open_redir_file(t_node *redir)
{
	int	fd;

	if (redir->kind == ND_REDIRECT_OUT)
		fd = open (redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->kind == ND_REDIRECT_APPEND)
		fd = open (redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redir->kind == ND_REDIRECT_IN)
		fd = open (redir->filename, O_RDONLY);
//	else if (redir->kind == ND_REDIRECT_HEREDOC)
//		return (heredoc);
	return (fd);
}

void	redirect_fd_list(t_node *redir)
{
	if (!redir)
		return ;
	while (redir)
	{
		redir->filefd = open_redir_file(redir);
		redir = redir->redirect;
	}
}

void	do_redirect(t_node *redir)
{
	int	old_fd;

	old_fd = STDOUT_FILENO;
	while (1)
	{
		if (!redir)
			break ;
		dup2(redir->filefd, old_fd);
		close(redir->filefd);//
		redir->savefd = old_fd;
		redir = redir->redirect;
	}
}
