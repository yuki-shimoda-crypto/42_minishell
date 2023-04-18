/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:40:30 by enogawa           #+#    #+#             */
/*   Updated: 2023/03/15 12:30:15 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(char **del_target, t_env **env_list)
{
	size_t	del_num;

	del_num = 1;
	while (del_target[del_num])
	{
		del_env(del_target[del_num], env_list);
		del_num++;
	}
	return (0);
}
