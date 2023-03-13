/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:51:52 by enogawa           #+#    #+#             */
/*   Updated: 2023/03/13 21:35:16 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_add(const char *env, t_env_list **env_list)
{
	char		*head;
	char		*tail;
	t_env_list	*new_list;
	char		*key;
	char		*value;

	if (!env || !env_list)
		return (1);
	tail = strchr(env, '=');
	if (!tail)
		return (0);
	key = strndup(env, tail - env);
	if (!key)
		assert_error("strndup\n");
	tail++;
	head = tail;
	






	env_list->key = substr(env, 0, (value_ptr - env));
	if (!env_list->key)
		return (1);
	env_list->value = strdup(value_ptr);
	if (!env_list->value)
		return (1);

	return (0);
}

void	make_env_list(char **envp)
{
	t_env_list	*env_list;
	t_env_list	*new;
	int			i;
	// t_env_list	*tmp;
	// char **temp;

	i = 0;
	env_list = calloc(1, sizeof(t_env_list));
	if (!env_list)
		error_func ("cannot alloate memory");
	if (env_add(envp[i], env_list))
		free_env(&env_list, 1);
	i++;
	while (envp[i])
	{
		new = env_new();
		if (env_add(envp[i], new))
			free_env(&env_list, 1);
		env_addback(&env_list, new);
		i++;
	}
}

	// i = env(env_list);
	// tmp = search_env("PWD", env_list);
	// printf ("\n%s\n\n", tmp->value);
	// del_env("PWD", env_list);
	// temp = malloc(sizeof(char *) * 1);
	// temp[0] = strdup("PWD");
	// i = unset(temp, env_list);
	// while (env_list)
	// {
	// 	printf ("%s", env_list->key);
	// 	printf ("%s\n", env_list->value);
	// 	env_list = env_list->next;
	// }