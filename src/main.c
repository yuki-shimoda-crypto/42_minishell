/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:52:04 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/01 11:28:33 by enogaWa          ###   ########.fr       */
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
			write (STDOUT_FILENO, "exit\n", ft_strlen("exit\n"));
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (ft_strlen(input))
				add_history(input);
			lexer(input);
			parser(input);
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
