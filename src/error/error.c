/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 23:26:00 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/16 14:20:15 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <unistd.h>

int	export_error(const char *cmd)
{
	write(STDERR_FILENO, PROMPT_ERROR, strlen(PROMPT_ERROR));
	write(STDERR_FILENO, "export: `", strlen("export: `"));
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, "': not a valid identifier\n",
		strlen("': not a valid identifier\n"));
	return (1);
}

void	env_error(const char *cmd)
{
	write(STDERR_FILENO, PROMPT_ERROR, strlen(PROMPT_ERROR));
	write(STDERR_FILENO, "env: `", strlen("env `"));
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, "`: No such file or directory\n",
		strlen("`: No such file or directory\n"));
}

int	unset_error(const char *cmd)
{
	write(STDERR_FILENO, PROMPT_ERROR, strlen(PROMPT_ERROR));
	write(STDERR_FILENO, "unset: `", strlen("unset: `"));
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, "': not a valid identifier\n",
		strlen("': not a valid identifier\n"));
	return (1);
}

void	exit_numeric(const char *cmd)
{
	write(STDERR_FILENO, "exit\n", strlen("exit\n"));
	write(STDERR_FILENO, PROMPT_ERROR, strlen(PROMPT_ERROR));
	write(STDERR_FILENO, "exit: ", strlen("exit: "));
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, ": numeric argument required\n",
		strlen(": numeric argument required\n"));
	exit (255);
}

void	cd_error(const char *cmd)
{
	write(STDERR_FILENO, PROMPT_ERROR, strlen(PROMPT_ERROR));
	write(STDERR_FILENO, "cd: ", strlen("cd: "));
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, " not set\n", strlen(" not set\n"));
}
