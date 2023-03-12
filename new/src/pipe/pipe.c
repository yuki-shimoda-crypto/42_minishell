/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:43:45 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/12 17:09:15 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

void	input_pipefd(t_node *node, int *inpipe)
{
	if (inpipe)
	{
		node->inpipe[0] = inpipe[0];
		node->inpipe[1] = inpipe[1];
	}
	if (node->pipe)
	{
		if (pipe(node->outpipe) == -1)
			assert_error("pipe\n");
		input_pipefd(node->pipe, node->outpipe);
	}
}

bool	is_redirect_in_exist(t_node *node)
{
	while (node)
	{
		if (node->kind == ND_REDIRECT_IN || node->kind == ND_REDIRECT_HEREDOC)
			return (true);
		node = node->redirect;
	}
	return (false);
}

bool	is_redirect_out_exist(t_node *node)
{
	while (node)
	{
		if (node->kind == ND_REDIRECT_OUT || node->kind == ND_REDIRECT_APPEND)
			return (true);
		node = node->redirect;
	}
	return (false);
}

void	connect_pipe(t_node *node)
{
	if (node->kind != ND_SIMPLE_CMD)
		return ;
	if (node->outpipe[1] != INT_MAX)
	{
		wrap_close(node->outpipe[0]);
		if (!is_redirect_out_exist(node))
		{
			if (node->outpipe[1] != 1)
			{
				wrap_dup2(node->outpipe[1], STDOUT_FILENO);
				wrap_close(node->outpipe[1]);
			}
		}
		else
			wrap_close(node->outpipe[1]);
	}

	if (node->inpipe[0] != INT_MAX)
	{
		wrap_close(node->inpipe[1]);
		if (!is_redirect_in_exist(node))
		{
			if (node->inpipe[0] != 0)
			{
				wrap_dup2(node->inpipe[0], STDIN_FILENO);
				wrap_close(node->inpipe[0]);
			}
		}
		else
			wrap_close(node->inpipe[0]);
	}
}

void	wrap_close(int fd)
{
	if (close(fd) == -1)
		assert_error("close\n");
}

void	wrap_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		assert_error("dup2\n");
}
