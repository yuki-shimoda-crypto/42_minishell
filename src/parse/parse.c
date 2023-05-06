/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 04:21:02 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/06 20:03:36 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

t_node	*new_node(t_node_kind kind, t_node *node_pre)
{
	t_node	*node;

	node = calloc(1, sizeof(t_node));
	if (!node)
		assert_error("calloc\n");
	node->kind = kind;
	if (node->kind == ND_REDIRECT_OUT || node->kind == ND_REDIRECT_APPEND)
		node->fd_target = STDOUT_FILENO;
	else if (node->kind == ND_REDIRECT_IN)
		node->fd_target = STDIN_FILENO;
	node->redirect_pre = node_pre;
	node->fd_save_inpipe = INT_MAX;
	node->fd_save_outpipe = INT_MAX;
	node->inpipe[0] = INT_MAX;
	node->inpipe[1] = INT_MAX;
	node->outpipe[0] = INT_MAX;
	node->outpipe[1] = INT_MAX;
	return (node);
}

void	make_redirect(t_node *node, t_tk *token)
{
	char	*filename;

	while (token->kind != TK_EOF && token->kind != TK_PIPE)
	{
		if (token->kind == TK_REDIRECT)
		{
			node->redirect = new_node(judge_nd_kind(token->word), node);
			filename = strdup(token->next->word);
			if (!filename)
				assert_error("strdup\n");
			node->redirect->filename = filename;
			node = node->redirect;
			token = token->next->next;
		}
		else
			token = token->next;
	}
}

void	make_simple_command(t_node *node, t_tk **skipped, t_tk *token)
{
	node->kind = ND_SIMPLE_CMD;
	node->token = dup_simple_command_token(skipped, token);
}

void	init_node(t_node *node)
{
	node->fd_save_inpipe = INT_MAX;
	node->fd_save_outpipe = INT_MAX;
	node->inpipe[0] = INT_MAX;
	node->inpipe[1] = INT_MAX;
	node->outpipe[0] = INT_MAX;
	node->outpipe[1] = INT_MAX;
	node->kind = ND_SIMPLE_CMD;
}

t_node	*parse(t_tk *token)
{
	t_node	*head;
	t_node	*node;

	node = calloc(1, sizeof(t_node));
	if (!node)
		assert_error("calloc");
	head = node;
	init_node(node);
	while (token && token->kind != TK_EOF)
	{
		make_redirect(node, token);
		if (token->kind != TK_PIPE)
			make_simple_command(node, &token, token);
		if (token->kind == TK_PIPE)
		{
			node->pipe = new_node(ND_PIPE, NULL);
			node = node->pipe;
			token = token->next;
		}
	}
	return (head);
}
