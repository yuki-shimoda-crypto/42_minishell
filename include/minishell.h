/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:53:27 by yshimoda          #+#    #+#             */
/*   Updated: 2023/02/20 16:42:12 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include "ft_printf.h"


// # define PROMPT "kimochiiii# "
# define PROMPT "きぃぃもちぃぃぃぃいい# "
// # define PROMPT "脳汁# "

// typedef struct s_cmd_lst
// {
// 	const char			**cmd;
// 	char				**redirections;
// 	size_t				s_quote_flag;
// 	size_t				d_quote_flag;
// 	long				output_redirection;
// 	pid_t				pid;
// 	struct s_cmd_lst	*pre;
// 	struct s_cmd_lst	*next;
// }		t_cmd_lst;

enum e_tk_kind
{
	TK_WORD,
	TK_PIPE,
	TK_OP,
	TK_EOF,
};
typedef enum e_tk_kind	t_tk_kind;

typedef struct s_token_list
{
	char				*token;
	t_tk_kind			kind;
	struct s_token_list	*next;
	// struct s_token_list	*prev;
}		t_token_list;

typedef struct s_env_list
{
	char				*value;
	char				*key;
	struct s_env_list	*next;
	struct s_env_list	*prev;
}	t_env_list;

// void		cmd_addback(t_cmd_lst **cmd_lst, t_cmd_lst *cmd_new);
// void		cmd_addfront(t_cmd_lst **cmd_lst, t_cmd_lst *cmd_new);
// void		cmd_clear(t_cmd_lst **cmd_lst);
// void		cmd_del_front(t_cmd_lst **cmd_lst);
// t_cmd_lst	*cmd_last(t_cmd_lst *cmd_lst);
// t_cmd_lst	*cmd_new(const char **cmd);
// size_t		cmd_size(t_cmd_lst *cmd_lst);
// int			split_count(char *input);
// int			find_next_quot(char *input, int i);
// void		split_by_space(t_lexer_utils *split_box, t_cmd_lst *separated);
void			error_func(const char *str);
// int				lexer(char *input);
int				parser(t_token_list	*token);
void			minishell_signal(void);
void			make_env_list(char **envp);
void			free_env(t_env_list **env_box, int flag);
void			free_env(t_env_list **env_box, int flag);
void			env_addback(t_env_list **env_list, t_env_list *env_new);
t_env_list		*env_last(t_env_list *env_list);
t_env_list		*env_new(void);
int				env(t_env_list	*env_box);
int				env_add(char *env, t_env_list *new);
t_env_list		*search_env(char *key_name, t_env_list *env_box);
void			del_env(char *key_name, t_env_list *env_box);
int				unset(char **del_target, t_env_list *env_box);
int				cd(char **destination, t_env_list *env_box);
// t_token_list	*tokenize(char *input);
t_token_list	*lexer(char *input);
void			exe(t_token_list *tk_list);

#endif
