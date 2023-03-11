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
	if (redir->kind == ND_REDIRECT_OUT || redir->kind == ND_REDIRECT_APPEND)	
	{
		if (dup2(redir->savefd, STDOUT_FILENO) == -1)
			assert_error("dup2\n");
	}
	else if (redir->kind == ND_REDIRECT_IN)
	{
		if (dup2(redir->savefd, STDIN_FILENO) == -1)
			assert_error("dup2\n");
	}
	// close(redir->savefd);
	// while (redir)
	// {
	// 	close(redir->filefd);
	// 	if (!redir->redirect)
	// 		dup2(STDOUT_FILENO, redir->filefd);
	// 	else
	// 		dup2(redir->savefd, redir->filefd);
	// 	redir = redir->redirect;
	// }
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

	if (!redir)
		return ;
	redir->savefd = FD_MAX;
	if (redir->kind == ND_REDIRECT_OUT || redir->kind == ND_REDIRECT_APPEND)	
		old_fd = STDOUT_FILENO;
	else if (redir->kind == ND_REDIRECT_IN)
		old_fd = STDIN_FILENO;
	if (dup2(old_fd, redir->savefd) == -1)
		assert_error("dup2\n");
	while (1)
	{
		if (!redir)
			break ;
		if (dup2(redir->filefd, old_fd) == -1)
			assert_error("dup2\n");
		close(redir->filefd);
		redir = redir->redirect;
	}
}
