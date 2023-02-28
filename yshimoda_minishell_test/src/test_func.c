#include "minishell.h"

void	print_node(t_node *node)
{
	while (node)	
	{
		printf("node_kind\t%d\n", node->kind);
		printf("node_ptr\t%p\n", node);
		printf("node_ptr_next\t%p\n", node->next);
		printf("node_args\t%s\n", node->args);	
		printf("node_args\t%s\n", node->redirects);	
	}
}

