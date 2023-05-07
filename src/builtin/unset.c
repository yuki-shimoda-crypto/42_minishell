/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:18:33 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 14:37:22 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_str_alpha_num_under_unset(const char *str)
{
	size_t	i;

	i = 1;
	while (str[0] && str[i])
	{
		if (!is_alpha_num_under(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	builtin_unset(char **argv, t_env **env_list)
{
	size_t	i;
	int		status;

	if (!argv[1])
		return (0);
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (!is_alpha_under(argv[i][0]))
		{
			status = unset_error(argv[i]);
			i++;
			continue ;
		}
		if (!is_str_alpha_num_under_unset(argv[i]))
		{
			status = unset_error(argv[i]);
			i++;
			continue ;
		}
		del_env(argv[i], env_list);
		i++;
	}
	return (status);
}
