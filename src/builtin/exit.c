/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:28:58 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 14:14:18 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <limits.h>
#include <ctype.h>

bool	is_number(const char *status)
{
	size_t	i;

	i = 0;
	while (status[i])
	{
		if (!ft_isdigit(status[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	ft_check_over(int sign, long ans, char c)
{
	long	tmp;

	tmp = LONG_MAX / 10;
	if (sign == 1)
		c++;
	if (tmp < ans || (tmp == ans && LONG_MAX % 10 + 1 < c - '0'))
		return (1);
	return (0);
}

bool	is_over_long(const char *str)
{
	int		sign;
	long	total;

	sign = 1;
	total = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		if (sign == 1 && ft_check_over(sign, total, *str))
			return (true);
		if (sign == -1 && ft_check_over(sign, total, *str))
			return (true);
		total = total * 10 + *str - '0';
		str++;
	}
	total *= sign;
	return (false);
}

int	builtin_exit(char **argv, bool one_cmd)
{
	long	status;

	status = 0;
	if (!argv[1])
	{
		if (isatty(STDIN_FILENO) && one_cmd)
			write(STDERR_FILENO, "exit\n", ft_strlen("exit\n"));
		exit(0);
	}
	else if (!argv[2])
	{
		if (argv[1][0] == '\0' || !is_number(argv[1]) || is_over_long(argv[1]))
			exit_numeric(argv[1]);
		status = ft_atol(argv[1]);
		if (one_cmd)
			write(STDERR_FILENO, "exit\n", ft_strlen("exit\n"));
		exit(status % 256);
	}
	else
	{
		write(STDERR_FILENO, "exit: too many arguments\n",
			ft_strlen("exit: too many arguments\n"));
		return (1);
	}
	return (0);
}
