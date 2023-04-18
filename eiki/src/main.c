/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:52:04 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/13 22:58:56 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[], char *envp[])
{
	char			*input;
	t_token_list	*tk_list;

	(void)argc;
	(void)argv;
	minishell_signal();
	make_env_list(envp);
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			write (STDOUT_FILENO, "exit\n", ft_strlen("exit\n"));
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (ft_strlen(input))
				add_history(input);
			tk_list = lexer(input);
			parser(tk_list);
			if (tk_list->token)
				exe(tk_list);
			// while (tk_list->kind != TK_EOF)//
			// {
			// 	printf("%d\n", tk_list->kind);
			// 	tk_list = tk_list->next;
			// }//
		}
		free(input);
	}
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q minishell");
// }
