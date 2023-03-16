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
		//printf("declare -x %s\n", sort_env[i]);
		write(1, "declare -x ", strlen("declare -x "));
		write(1, sort_env[i], strlen(sort_env[i]));
		write(1, "\n", 1);
		i++;
	}
	free_array(sort_env);
}

void	overwrite_env(const char *env, t_env *env_list)
{
	char	*value;
	char	*value_head;

	value_head = strchr(env, '=');
	value_head++;
	value = strdup(value_head);
	if (!value)
		assert_error("strdup");
	while (env_list)
	{
		if (!strncmp(env, env_list->key, strlen(env_list->key)))
		{
			free(env_list->value);
			env_list->value = value;
			break ;
		}
		env_list = env_list->next;
	}
}

static void	handle_env(char **argv, t_env **env_list)
{
	size_t	i;
	char	*eq_ptr;

	i = 1;
	while (argv[i])
	{
		if (!is_alpha_under(argv[i][0]))
		{
			export_error(argv[i]);
			i++;
			continue ;
		}
		eq_ptr = strchr(argv[i], '=');
		if (!eq_ptr)
		{
			i++;
			continue ;
		}
		if (is_key_exist(argv[i], *env_list))
			overwrite_env(argv[i], *env_list);
		else
			add_env(argv[i], env_list);
		i++;
	}
}

int	builtin_export(char **argv, t_env **env_list)
{
	size_t	num;

	if (!argv || !*argv || !env_list)
		return (1);
	num = 0;
	while (argv[num])
		num++;
	if (num == 1)
		put_sorted_env(*env_list);
	else
		handle_env(argv, env_list);
	return (0);
}
