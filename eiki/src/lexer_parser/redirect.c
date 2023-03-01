/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:47:49 by enogaWa           #+#    #+#             */
/*   Updated: 2023/02/28 18:40:44 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_fd_list	*fd_last(t_fd_list	*fd_list)
{
	if (!fd_list)
		return (NULL);
	while (fd_list->next)
		fd_list = fd_list->next;
	return (fd_list);
}

static void	fd_addback(t_fd_list **fd_list, t_fd_list *fd_new)
{
	t_fd_list	*last;

	if (!fd_list || ! fd_new)
		return ;
	if (!*fd_list)
	{
		*fd_list = fd_new;
		return ;
	}
	last = fd_last(*fd_list);
	last->next = fd_new;
	return ;
}

static t_fd_list	*new_fd_list(int fd)
{
	t_fd_list	*new;

	new = ft_calloc(1, sizeof(t_fd_list));
	// if (!new)
	// 	error_func(calloc);
	new->fd = fd;
	new->next = NULL;
	return (new);
}

static int	get_fd(t_token_list	*tk)
{
	int	fd;

	if (ft_strncmp(tk->token, ">", ft_strlen(tk->token)) == 0)
		fd = open (tk->next->token, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (ft_strncmp(tk->token, ">>", ft_strlen(tk->token)) == 0)
		fd = open (tk->next->token, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

static void	make_fd_list(t_token_list	*tk, t_fd_list	*fd_list)
{
	t_fd_list	*new;
	int			fd;

	while (tk->kind != TK_EOF)
	{
		if (tk->kind == TK_OP)
		{
			if (fd_list->fd == -1)
				fd_list->fd = get_fd(tk);
			else
			{
				fd = get_fd(tk);
				new = new_fd_list(fd);
				fd_addback(&fd_list, new);
			}
		}
		tk = tk->next;
	}
}

void	redirection(t_token_list	*tk_list)
{
	int				old_fd;
	t_fd_list		*fd_list;
	t_token_list	*tk;

	tk = tk_list;
	old_fd = 1;
	fd_list = ft_calloc(1, sizeof(t_fd_list));
	fd_list->fd = -1;
	make_fd_list(tk, fd_list);
	while (1)
	{
		if (old_fd != fd_list->fd)
		{
			dup2(fd_list->fd, old_fd);
		}
		if (!fd_list->next)
			break ;
		fd_list = fd_list->next;
	}
}
