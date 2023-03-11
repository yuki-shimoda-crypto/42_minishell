/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 04:21:02 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/07 16:58:221 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	new_node_redirect(t_node *node, t_tk *token)
// {
// 	t_tk	*tmp;

// 	tmp = token->next->next;
// 	node->redirect = calloc(1, sizeof(t_node));
// 	if (!node->redirect)
// 		assert_error("calloc");
// 	node->redirect->filename = token->next->word;
// 	free(token->word);
// 	free(token->next->word);
// 	free(token);
// 	free(token->next)
// 	return (token->next->next);
// }

int	judge_nd_kind(char *redirect)
{
	if (!strncmp(redirect, ">>", 2))
		return (ND_REDIRECT_APPEND);
	else if (!strncmp(redirect, "<<", 2))
		return (ND_REDIRECT_HEREDOC);
	else if (!strncmp(redirect, ">", 1))
		return (ND_REDIRECT_OUT);
	else if (!strncmp(redirect, "<", 1))
		return (ND_REDIRECT_IN);
	return (0);
}

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
t_tk	*dup_token(char *word)
{
	t_tk	*token;

	token = calloc(1, sizeof(t_tk));
	if (!token)
		assert_error("calloc");
	token->word = strdup(word);
	token->kind = TK_WORD;
	return (token);
}

t_tk	*dup_simple_command_token(t_tk **skipped, t_tk *token)
{
	t_tk	head;
	t_tk	*new_token;

	new_token = &head;
	new_token->word = NULL;
	new_token->kind = TK_WORD;
	new_token->next = NULL;
	while (token->kind != TK_EOF && token->kind != TK_PIPE)
	{
		if (token->kind == TK_REDIRECT)
			token = token->next->next;
		else
		{
			new_token->next = dup_token(token->word);
			new_token = new_token->next;
			token = token->next;
		}
	}
	new_token->next = token_new(NULL, TK_EOF);
	*skipped = token;
	return (head.next);
}

void	make_simple_command(t_node *node, t_tk **skipped, t_tk *token)
{
	node->kind = ND_SIMPLE_CMD;
	node->token = dup_simple_command_token(skipped, token);
}

t_node	*parse(t_tk *token)
{
	t_node	*head;
	t_node	*node;

	node = calloc(1, sizeof(t_node));
	if (!node)
		assert_error("calloc");
	head = node;
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
