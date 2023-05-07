/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 23:26:00 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 14:14:18 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <unistd.h>

int	export_error(const char *cmd)
{
	write(STDERR_FILENO, PROMPT_ERROR, ft_strlen(PROMPT_ERROR));
	write(STDERR_FILENO, "export: `", ft_strlen("export: `"));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, "': not a valid identifier\n",
		ft_strlen("': not a valid identifier\n"));
	return (1);
}

void	env_error(const char *cmd)
{
	write(STDERR_FILENO, PROMPT_ERROR, ft_strlen(PROMPT_ERROR));
	write(STDERR_FILENO, "env: `", ft_strlen("env `"));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, "`: No such file or directory\n",
		ft_strlen("`: No such file or directory\n"));
}

int	unset_error(const char *cmd)
{
	write(STDERR_FILENO, PROMPT_ERROR, ft_strlen(PROMPT_ERROR));
	write(STDERR_FILENO, "unset: `", ft_strlen("unset: `"));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, "': not a valid identifier\n",
		ft_strlen("': not a valid identifier\n"));
	return (1);
}

void	exit_numeric(const char *cmd)
{
	write(STDERR_FILENO, "exit\n", ft_strlen("exit\n"));
	write(STDERR_FILENO, PROMPT_ERROR, ft_strlen(PROMPT_ERROR));
	write(STDERR_FILENO, "exit: ", ft_strlen("exit: "));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": numeric argument required\n",
		ft_strlen(": numeric argument required\n"));
	exit (255);
}

void	cd_error(const char *cmd)
{
	write(STDERR_FILENO, PROMPT_ERROR, ft_strlen(PROMPT_ERROR));
	write(STDERR_FILENO, "cd: ", ft_strlen("cd: "));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, " not set\n", ft_strlen(" not set\n"));
}
