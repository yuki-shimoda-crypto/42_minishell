/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 00:28:31 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/07 01:55:09 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ok
bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

// ok
bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

// ok
bool	is_quoted(char c, char *line)
{
	if (c == '\'' || c == '"')
	{
		while (*line)
		{
			line++;
			if (*line == c)
				return (true);
		}
	}
	return (false);
}

// ok_yshimoda
static bool	is_redirect_error(char *line)
{
	if (!strncmp(line, "<>", 2))
		return (true);
	else if (!strncmp(line, "><", 2))
		return (true);
	else if (!strncmp(line, ">>>", 3))
		return (true);
	else if (!strncmp(line, ">><", 3))
		return (true);
	else if (!strncmp(line, "<<<", 3))
		return (true);
	else if (!strncmp(line, "<<>", 3))
		return (true);
	return (false);
}

bool	is_redirect(char c, char **skipped, char *line)
{
	if (is_redirect_error(line))
	{
		syntax_error("< or >\n", skipped, line);
		g_return_error.tokenize_error = true;
		return (false);
	}
	else if (!strncmp(line, ">>", 2) || !strncmp(line, "<<", 2))
		return (true);
	return (c == '>' || c == '<');
}
