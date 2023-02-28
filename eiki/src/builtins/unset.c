/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogawa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:40:30 by enogawa           #+#    #+#             */
/*   Updated: 2023/01/14 03:18:31 by enogawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(char **del_target, t_env_list *env_box)
{
	size_t	del_num;

	del_num = 1;
	while (del_target[del_num])
	{
		del_env(del_target[del_num], env_box);
		del_num++;
	}
	return (0);
}
