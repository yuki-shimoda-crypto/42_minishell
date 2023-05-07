/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:04:47 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 13:17:38 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_env_list(t_env *env_list)
{
	while (env_list)
	{
		printf("key:\t%s\n", env_list->key);
		printf("value:\t%s\n", env_list->value);
		printf("pre:\t%p\n", env_list->pre);
		printf("now:\t%p\n", env_list);
		printf("next:\t%p\n", env_list->next);
		printf("%s\n", "------------");
		env_list = env_list->next;
	}
}

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
	printf("node->token\t%p\n", node->token);
	printf("node->redirect\t%p\n", node->redirect);
	printf("node_redirect_pre\t%p\n", node->redirect_pre);
	if (node->filename)
		printf("node_filename\t%s\n", node->filename);
	print_t_tk(node->token);
	printf("node_ptr\t%p\n", node);
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
	while (token)
	{
		printf("token_word\t%s\n", token->word);
		printf("token_kind\t%s\n", print_t_tk_kind(token->kind));
		if (token->kind == TK_EOF)
			break ;
		token = token->next;
	}
}
