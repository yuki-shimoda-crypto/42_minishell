/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 02:02:39 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 14:14:18 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

bool	is_file(const char *pathname)
{
	size_t	len;

	if (!pathname)
		return (false);
	len = ft_strlen(pathname);
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

bool	is_only_slash(const char *pathname)
{
	size_t	i;

	if (!pathname || !*pathname)
		return (false);
	i = 0;
	while (pathname[i])
	{
		if (pathname[i] != '/')
			return (false);
		i++;
	}
	return (true);
}

bool	is_directory(const char *pathname)
{
	struct stat	st;

	if (stat(pathname, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (true);
	}
	return (false);
}
