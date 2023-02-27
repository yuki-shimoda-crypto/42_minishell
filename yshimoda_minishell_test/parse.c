#include "minishell.h"
#include <string.h>
#include <stdlib.h>

t_node	*parse(t_token *tok)
{
	t_node	*node;
	
	node = new_node(ND_SIMPLE_CMD);
	append_command_element(node, &tok, tok);
	while (tok && !at_eof(tok))
		append_command_element(node, &tok, tok);
	return (node);
}

t_node	*redirect_out(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	append_command_element(node, &tok, tok);
	while (tok && !at_eof(tok))
		append_command_element(node, &tok, tok);
	return (node);
}

void	append_command_element(t_node *command, t_token **rest, t_token *tok)
{
	if (tok->kind == TK_WORD)
	{
		append_tok(&command->args, tokdup(tok));
		tok = tok->next;
	}
	else if (equal_op(tok, ">") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_out(&tok, tok));
	else
		todo("append_command_element");
	*rest = tok;
}

bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

bool	equal_op(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (false);
	return (strcmp(tok->word, op) == 0);
}

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = calloc(1, sizeof(*node));
	if (node == NULL)
		fatal_error("calloc");
	node->kind = kind;
	return (node);
}

t_token	*tokdup(t_token *tok)
{
	char	*word;
	
	word = strdup(tok->word);
	if (word == NULL)
		fatal_error("strdup");
	return (new_token(word, tok->kind));
}

void	append_tok(t_token **tok, t_token *elm)
{
	if (*tok == NULL)
	{
		*tok = elm;
		return ;
	}
	append_tok(&(*tok)->next, elm);
}

void	append_node(t_node **node, t_node *elm)
{
	if (*node == NULL)
	{
		*node == elm;
		return ;
	}
	append_node(&(*node)->next, elm);
}

