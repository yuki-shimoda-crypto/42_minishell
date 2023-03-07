/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:04:47 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/07 21:34:24 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static const char	*print_t_node_kind(int kind)
{
	if (kind == ND_SIMPLE_CMD)
		return ("ND_SIMPLE_CMD");
	if (kind == ND_REDIRECT_OUT)
		return ("ND_REDIRECT_OUT");
	if (kind == ND_REDIRECT_IN)
		return ("ND_REDIRECT_IN");
	if (kind == ND_REDIRECT_APPEND)
		return ("ND_REDIRECT_APPEND");
	if (kind == ND_REDIRECT_HEREDOC)
		return ("ND_REDIRECT_HEREDOC");
	if (kind == ND_PIPE)
		return ("ND_PIPE");
	return (NULL);
}

void	print_node(t_node *node, int i)
{
	printf("%s\n", "----------");
	printf("rank\t\t%d\n", i);
	printf("node_kind\t%s\n", print_t_node_kind(node->kind));
	if (node->filename)
		printf("node_filename\t%s\n", node->filename);
	print_t_tk(node->token);
	printf("%s\n", "----------");
	if (node->redirect)
		print_node(node->redirect, i + 1);
	if (node->pipe)
		print_node(node->pipe, i + 1);
}

const char	*print_t_tk_kind(int kind)
{
	if (kind == TK_WORD)
		return ("TK_WORD");
	if (kind == TK_REDIRECT)
		return ("TK_REDIRECT");
	if (kind == TK_PIPE)
		return ("TK_PIPE");
	if (kind == TK_EOF)
		return ("TK_EOF");
	return (NULL);
}

void	print_t_tk(t_tk	*token)
{
	while (token && token->kind != TK_EOF)
	{
		printf("token_word\t%s\n", token->word);
		printf("token_kind\t%s\n", print_t_tk_kind(token->kind));
		token = token->next;
	}
}
