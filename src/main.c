/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogawa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:52:04 by yshimoda          #+#    #+#             */
/*   Updated: 2022/12/09 21:55:44 by enogawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	main(int argc, char const *argv[])
{
	(void)argc;
	char *input;

	while (1)
	{
		input = readline(PROMPT);
		add_history(input);
		ft_printf("%s\n", input);
		free(input);
	}
	ft_printf("%s\n", argv[0]);
	return (0);
}

__attribute__((destructor)) static void destructor()
{
	system("leaks -q minishell");
}
