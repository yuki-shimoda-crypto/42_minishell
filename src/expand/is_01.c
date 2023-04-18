/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:34:41 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/13 10:46:35 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

bool	is_single_quote(const char c)
{
	return (c == '\'');
}

bool	is_double_quote(const char c)
{
	return (c == '"');
}

bool	is_variable(char *line)
{
	return (line[0] == '$' && is_alpha_under(line[1]));
}

bool	is_alpha_under(char c)
{
	return (isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || isdigit(c));
}
