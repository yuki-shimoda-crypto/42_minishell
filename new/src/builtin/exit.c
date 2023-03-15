/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:28:58 by enogaWa           #+#    #+#             */
/*   Updated: 2023/03/15 12:53:16 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <limits.h>
#include <ctype.h>

static int	check_num(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		if (!isdigit(str[len]))
			return (1);
		if (len >= 20)
			return (1);
		len++;
	}
	return (0);
}

static int	check_overflow(unsigned long ans, int sign)
{
	if (sign == 1)
	{
		if (ans > LONG_MAX)
			return (-1);
	}
	else if (sign == -1)
	{
		ans -= 1;
		if (ans > LONG_MAX)
			return (1);
	}
	return (0);
}

static int	atoi_for_exit(char *cmd)
{
	unsigned long	i;
	unsigned long	ans;
	int				sign;

	i = 0;
	sign = 1;
	while (cmd[i] == '\t' || cmd[i] == '\n' || cmd[i] == '\v'
		|| cmd[i] == '\f' || cmd[i] == '\r' || cmd[i] == ' ')
		i++;
	if (cmd[i] == '-')
		sign = -1;
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	if (check_num(&cmd[i]) != 0)
		exit_numeric(cmd);
	while (isdigit(cmd[i]))
	{
		ans = ans * 10 + cmd[i] - '0';
		i++;
	}
	if (!check_overflow(ans, sign))
		exit_numeric(cmd);
	return (ans * sign);
}

int	builtin_exit(char **argv)
{
	int	status;

	status = 0;
	if (!argv[1])
	{
		printf("exit\n");
		exit (0);
	}
	else if (!argv[2])
	{
		status = atoi_for_exit(argv[1]);
		printf("exit\n");
		exit(status % 256);
	}
	else
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	return (0);
}
