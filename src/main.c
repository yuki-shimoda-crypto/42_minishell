/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:52:04 by yshimoda          #+#    #+#             */
/*   Updated: 2022/12/13 16:59:19 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[], char **envp)
{
	(void)argc;
	(void)envp;
	char *input;
	
	minishell_signal();
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			write (1, "exit\n", 6);
			exit(EXIT_SUCCESS);
		}
		else
		{
			add_history(input);
			ft_lexer(input);//字句解析
			ft_parser(input);//構文解析
		}
		ft_printf("%s\n", input);
		free(input);
	}
	ft_printf("%s\n", argv[0]);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q minishell");
// }
