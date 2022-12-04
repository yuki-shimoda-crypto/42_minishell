/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:52:04 by yshimoda          #+#    #+#             */
/*   Updated: 2022/12/05 00:13:09 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char const *argv[])
{
	(void)argc;
	ft_printf("%s\n", argv[0]);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q minishell");
// }
