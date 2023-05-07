/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 04:15:24 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 11:10:22 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	exec(char *pathname, char **argv, char **envp, t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		assert_error("fork\n");
	else if (pid == 0)
	{
		connect_pipe(node);
		execve(pathname, argv, envp);
		assert_error("execve\n");
	}
}

void	exec_command(t_node *node, t_env **env_list, t_exec *exec_val)
{
	if (exec_val->argv && is_builtin(exec_val->argv[0]) && exec_val->one_cmd)
		exec_builtin(node, env_list, exec_val);
	else
	{
		exec_val->pid = fork();
		if (exec_val->pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (exec_val->pid == 0)
			handle_child_process(node, env_list, exec_val);
		else
			handle_parent_process(node, exec_val);
	}
}

void	exec_cmd_in_loop(t_node *node, t_env **env_list, t_exec *exec_val)
{
	while (node)
	{
		exec_val->pathname = make_pathname(node->token, *env_list);
		if (should_continue(&node, exec_val, g_return_error.error, false))
			continue ;
		exec_val->argv = make_argv(node->token);
		if (should_continue(&node, exec_val, !exec_val->argv, false))
			continue ;
		redirect_fd_list(node->redirect, *env_list);
		if (should_continue(&node, exec_val, g_return_error.error, true))
			continue ;
		do_redirect(node->redirect);
		if (should_continue(&node, exec_val,
				node->token->kind != TK_WORD, true))
		{
			reset_redirect(node->redirect);
			continue ;
		}
		exec_command(node, env_list, exec_val);
		reset_redirect(node->redirect);
		node = node->pipe;
		free(exec_val->pathname);
		free_argv(exec_val->argv);
	}
}

void	exec_cmd(t_node *node, t_env **env_list)
{
	t_exec	exec_val;

	input_pipefd(node, NULL);
	expand(node, *env_list);
	init_exec_val(&exec_val);
	exec_val.envp = make_envp(*env_list);
	if (!node->pipe)
		exec_val.one_cmd = true;
	exec_cmd_in_loop(node, env_list, &exec_val);
	free_envp(exec_val.envp);
	wait_child_process(&exec_val);
}
