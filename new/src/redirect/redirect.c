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
	t_node	*last;

	if (!redir)
		return ;
	last = redir;
	while (last->redirect)
		last = last->redirect;
	while (1)
	{
		wrap_close(last->fd_target);
		if (dup2(last->fd_save, last->fd_target) == -1)
			assert_error("dup2\n");
		wrap_close(last->fd_save);
		if (last == redir)
			break ;
		last = last->redirect_pre;
	}
}

int	open_redir_file(t_node *redir)
{
	int	fd;

	fd = 0;
	if (redir->kind == ND_REDIRECT_OUT)
	{
		fd = open (redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(redir->filename);
			g_return_error.redirect_error = true;
		}
	}
	else if (redir->kind == ND_REDIRECT_APPEND)
	{
		fd = open (redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(redir->filename);
			g_return_error.redirect_error = true;
		}
	}
	else if (redir->kind == ND_REDIRECT_IN)
	{
		fd = open (redir->filename, O_RDONLY);
		if (fd == -1)
		{
			perror(redir->filename);
			g_return_error.redirect_error = true;
		}
	}
	else if (redir->kind == ND_REDIRECT_HEREDOC)
		fd = heredoc(redir->filename);
	return (fd);
}

void	redirect_fd_list(t_node *redir)
{
	if (!redir)
		return ;
	while (redir)
	{
		redir->fd_file = open_redir_file(redir);
		redir = redir->redirect;
	}
}

void	do_redirect(t_node *redir)
{
	if (!redir)
		return ;
	while (redir)
	{
		redir->fd_save = dup(redir->fd_target);
		if (redir->fd_save == -1)
			assert_error("dup\n");
		close(redir->fd_target);
		if (dup2(redir->fd_file, redir->fd_target) == -1)
			assert_error("dup2\n");
		close(redir->fd_file);
		redir = redir->redirect;
	}
}
