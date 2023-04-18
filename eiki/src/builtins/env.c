/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:19:02 by enogawa           #+#    #+#             */
/*   Updated: 2023/03/02 17:36:13 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_env_list	*env_box)
{
	while (env_box)
	{
		ft_putstr_fd(env_box->key, STDOUT_FILENO);
		ft_putendl_fd(env_box->value, STDOUT_FILENO);
		env_box = env_box->next;
	}
	printf("_=/usr/bin/env\n");
	return (0);
}
