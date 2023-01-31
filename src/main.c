/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogawa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:52:04 by yshimoda          #+#    #+#             */
/*   Updated: 2023/01/17 11:07:10 by enogawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[], char **envp)
{
	// char	*input;

	(void)argc;
	(void)argv;
	minishell_signal();
	make_env_list(envp);
	// while (1)
	// {
	// 	input = readline(PROMPT);
	// 	if (!input)
	// 	{
	// 		write (STDOUT_FILENO, "exit\n", ft_strlen("exit\n"));
	// 		exit(EXIT_SUCCESS);
	// 	}
	// 	else
	// 	{
	// 		if (ft_strlen(input))
	// 			add_history(input);
	// 		if (lexer(input))
	// 			continue ;
	// 		parser(input);
	// 	}
	// 	free(input);
	return (0);
	}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q minishell");
// }
