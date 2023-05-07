/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:34:41 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 15:18:07 by yshimoda         ###   ########.fr       */
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
	return (ft_isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || ft_isdigit(c));
}
