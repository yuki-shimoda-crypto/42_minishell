/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 10:02:23 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 10:17:41 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_relative_path(const char *word)
{
	size_t	len;

	len = strlen(word);
	if (2 <= len && !strncmp(word, "./", 2))
		return (true);
	if (3 <= len && !strncmp(word, "../", 3))
		return (true);
	return (false);
}

bool	is_dot(const char *word)
{
	size_t	len;

	len = strlen(word);
	if (len == 1 && !strncmp(word, ".", 1))
		return (true);
	else if (len == 2 && !strncmp(word, "..", 2))
		return (true);
	return (false);
}
