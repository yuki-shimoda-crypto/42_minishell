/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogawa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:51:52 by enogawa           #+#    #+#             */
/*   Updated: 2023/01/14 04:23:31 by enogawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_add(char *env, t_env_list *new)
{
	char		*value_ptr;

	value_ptr = ft_strchr(env, '=');
	if (!value_ptr)
		return (1);
	if (!new)
		return (1);
	new->key = ft_substr(env, 0, (value_ptr - env));
	if (!new->key)
		return (1);
	new->value = ft_strdup(value_ptr);
	if (!new->value)
		return (1);
	return (0);
}

void	make_env_list(char **envp)
{
	t_env_list	*env_box;
	t_env_list	*new;
	int			i;
	// t_env_list	*tmp;
	// char **temp;

	i = 0;
	env_box = ft_calloc(1, sizeof(t_env_list));
	if (!env_box)
		error_func ("cannot alloate memory");
	if (env_add(envp[i], env_box))
		free_env(&env_box, 1);
	i++;
	while (envp[i])
	{
		new = env_new();
		if (env_add(envp[i], new))
			free_env(&env_box, 1);
		env_addback(&env_box, new);
		i++;
	}
}

	// i = env(env_box);
	// tmp = search_env("PWD", env_box);
	// printf ("\n%s\n\n", tmp->value);
	// del_env("PWD", env_box);
	// temp = malloc(sizeof(char *) * 1);
	// temp[0] = ft_strdup("PWD");
	// i = unset(temp, env_box);
	// while (env_box)
	// {
	// 	printf ("%s", env_box->key);
	// 	printf ("%s\n", env_box->value);
	// 	env_box = env_box->next;
	// }