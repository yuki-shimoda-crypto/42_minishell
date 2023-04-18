/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 02:02:39 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/09 02:06:16 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_file(const char *pathname)
{
	size_t	len;

	if (!pathname)
		return (false);
	len = strlen(pathname);
	if (len != 0 && pathname[len - 1] == '/')
		return (false);
	return (true);
}

bool	is_file_executable(const char *pathname)
{
	if (!access(pathname, X_OK))
		return (true);
	return (false);
}

bool	is_file_exist(const char *pathname)
{
	if (!access(pathname, F_OK))
		return (true);
	return (false);
}
