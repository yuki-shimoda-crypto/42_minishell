/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 10:02:23 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 14:15:18 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_relative_path(const char *word)
{
	size_t	len;

	len = ft_strlen(word);
	if (2 <= len && !ft_strncmp(word, "./", 2))
		return (true);
	if (3 <= len && !ft_strncmp(word, "../", 3))
		return (true);
	return (false);
}

bool	is_dot(const char *word)
{
	size_t	len;

	len = ft_strlen(word);
	if (len == 1 && !ft_strncmp(word, ".", 1))
		return (true);
	else if (len == 2 && !ft_strncmp(word, "..", 2))
		return (true);
	return (false);
}
