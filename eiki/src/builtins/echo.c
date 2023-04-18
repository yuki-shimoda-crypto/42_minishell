/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:57:09 by enogawa           #+#    #+#             */
/*   Updated: 2023/03/02 16:42:50 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

void	echo(t_cmd_lst	*separated)
{
	int	i;

	i = 1;
	if (separated->cmd[i] == "-n")
		i++;
	while (separated->cmd[i])
	{
		ft_printf("%s", separated->cmd[i]);
		i++;
	}
	if (!separated->cmd[1] == "-n")
		write(STDOUT_FILENO, '\n', 1);
}
