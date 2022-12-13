/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:52:04 by yshimoda          #+#    #+#             */
/*   Updated: 2022/12/14 04:53:35 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[], char **envp)
{
	char	*input;

	(void)argc;
	(void)envp;
	minishell_signal();
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			write (STDERR_FILENO, "exit\n", ft_strlen("exit\n"));
			exit(EXIT_SUCCESS);
		}
		else
		{
			add_history(input);
			ft_lexer(input);
			ft_parser(input);
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
