/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 01:58:47 by yshimoda          #+#    #+#             */
/*   Updated: 2022/12/15 11:42:10 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_func(const char *str)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd((char *)str, STDERR_FILENO);
	exit(EXIT_FAILURE);
	return ;
}
