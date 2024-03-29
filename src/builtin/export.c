/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:33:27 by enogaWa           #+#    #+#             */
/*   Updated: 2023/05/07 14:36:09 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>

static void	put_sorted_env(t_env *env_list)
{
	char	**sort_env;
	size_t	i;

	if (!env_list)
		return ;
	sort_env = env_into_array(env_list);
	sort_array(sort_env);
	i = 0;
	while (sort_env[i])
	{
		write(1, "declare -x ", ft_strlen("declare -x "));
		write(1, sort_env[i], ft_strlen(sort_env[i]));
		if (ft_strchr(sort_env[i], '='))
			write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
	free_array(sort_env);
}

void	overwrite_env(const char *env, t_env *env_list)
{
	char	*value;
	char	*value_head;

	value_head = ft_strchr(env, '=');
	if (!value_head)
		return ;
	value_head++;
	value = ft_strdup(value_head);
	if (!value)
		assert_error("ft_strdup");
	while (env_list)
	{
		if (!ft_strncmp(env, env_list->key, ft_strlen(env_list->key)))
		{
			free(env_list->value);
			env_list->value = value;
			break ;
		}
		env_list = env_list->next;
	}
}

static bool	is_str_alpha_num_under_export(const char *str)
{
	size_t	i;
	char	*ptr_equal;

	ptr_equal = ft_strchr(str, '=');
	i = 1;
	while (str[0] && str[i])
	{
		if (ptr_equal == str + i)
			break ;
		if (!is_alpha_num_under(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	handle_env(char **argv, t_env **env_list)
{
	size_t	i;
	int		status;

	i = 1;
	while (argv[i])
	{
		if (!is_alpha_under(argv[i][0]))
		{
			status = export_error(argv[i]);
			i++;
			continue ;
		}
		if (!is_str_alpha_num_under_export(argv[i]))
		{
			status = export_error(argv[i]);
			i++;
			continue ;
		}
		if (is_key_exist(argv[i], *env_list))
			overwrite_env(argv[i], *env_list);
		else
			add_env(argv[i], env_list);
		i++;
	}
	return (status);
}

int	builtin_export(char **argv, t_env **env_list)
{
	size_t	num;
	int		status;

	status = 0;
	if (!argv || !*argv || !env_list)
		return (1);
	num = 0;
	while (argv[num])
		num++;
	if (num == 1)
		put_sorted_env(*env_list);
	else
		status = handle_env(argv, env_list);
	return (status);
}
