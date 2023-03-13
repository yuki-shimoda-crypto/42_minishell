/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:51:52 by enogawa           #+#    #+#             */
/*   Updated: 2023/03/14 03:59:22 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


extern char	**environ;
int main(void)
{
	t_env	*env_list;

	env_list = make_env_list(environ);
	// print_env_list(env_list);
	while (env_list)
		del_env(env_list->key, &env_list);
	printf("%p\n", env_list);
	add_env("42tokyokami=", &env_list);
	add_env("42tokyomaji=", &env_list);
	print_env_list(env_list);
	free_env(&env_list);
}

