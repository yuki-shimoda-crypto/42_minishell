/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:18:33 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/30 18:03:49 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv, t_env **env_list)
{
	size_t	i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		if (strchr(argv[i], '='))
		{
			unset_error(argv[i]);
			return (1);
		}
		del_env(argv[i], env_list);
		i++;
	}
	return (0);
}
