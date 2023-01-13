/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogawa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:02:35 by enogawa           #+#    #+#             */
/*   Updated: 2023/01/14 04:19:37 by enogawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// static int	exit_numeric(char *cmd)
// {
// 	ft_putstr_fd("exit: ", STDERR_FILENO);
// 	write(STDERR_FILENO, cmd, ft_strlen(cmd));
// 	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
// 	exit (255);
// }

// static int	check_num(char *str)
// {
// 	size_t	len;

// 	len = 0;
// 	while (str[len])
// 	{
// 		if (!ft_isdigit(str[len]))
// 			return (1);
// 		if (len >= 20)
// 			return (1);
// 	}
// 	return (0);
// }

// static int	check_overflow(unsigned long ans, int sign)
// {
// 	if (sign == 1)
// 	{
// 		if (ans > LONG_MAX)
// 			return (-1);
// 	}
// 	else if (sign == -1)
// 	{
// 		ans -= 1;
// 		if (ans > LONG_MAX)
// 			return (1);
// 	}
// 	return (0);
// }

// static int	atoi_for_exit(char *cmd)
// {
// 	unsigned long	i;
// 	unsigned long	ans;
// 	int				sign;

// 	i = 0;
// 	sign = 1;
// 	while (cmd[i] == '\t' || cmd[i] == '\n' || cmd[i] == '\v'
// 		|| cmd[i] == '\f' || cmd[i] == '\r' || cmd[i] == ' ')
// 		i++;
// 	if (cmd[i] == '-')
// 		sign = -1;
// 	if (cmd[i] == '-' || cmd[i] == '+')
// 		i++;
// 	if (check_num(&cmd[i]) != 0)
// 		exit_numeric(cmd);
// 	while (ft_isdigit(cmd[i]))
// 	{
// 		ans = ans * 10 + cmd[i] - '0';
// 		i++;
// 	}
// 	if (!check_overflow(ans, sign))
// 		exit_numeric(cmd);
// 	return (ans * sign);
// }

// int	builtin_exit(t_cmd_lst	*separated)
// {
// 	int	i;
// 	int	len;
// 	int	status;

// 	i = 0;
// 	len = 0;
// 	status = 0;
// 	while (separated->cmd[i])
// 		len++;
// 	if (len == 1)
// 	{
// 		ft_putendl_fd("exit", STDOUT_FILENO);
// 		exit (0);
// 	}
// 	else if (len == 2)
// 	{
// 		status = atoi_for_exit(separated->cmd[1]);
// 		ft_putendl_fd("exit", STDERR_FILENO);
// 		exit(status % 256);
// 	}
// 	else if (len >= 3)
// 	{
// 		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
// 		return (1);
// 	}
// }
