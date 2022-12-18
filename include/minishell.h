/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:53:27 by yshimoda          #+#    #+#             */
/*   Updated: 2022/12/18 19:21:39 by yshimoda         ###   ########.fr       */
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
# include "libft.h"
# include "ft_printf.h"

// # define PROMPT "kimochiiii# "
# define PROMPT "きぃぃもちぃぃぃぃいい# "
// # define PROMPT "脳汁# "

typedef struct s_cmd
{
	const char			*cmd;
	char				**cmd_option;
	char				**redirections;
	size_t				s_quote_flag;
	size_t				d_quote_flag;
	long				output_redirection;
	pid_t				pid;
	struct s_cmd_lst	*pre;
	struct s_cmd_lst	*next;
}		t_cmd_lst;

void		error_func(const char *str);
int			lexer(char *input);
void		minishell_signal(void);
int			parser(char *input);
void		cmd_addback(t_cmd_lst **cmd_lst, t_cmd_lst *cmd_new);
void		cmd_addfront(t_cmd_lst **cmd_lst, t_cmd_lst *cmd_new);
void		cmd_clear(t_cmd_lst **cmd_lst);
void		cmd_del_front(t_cmd_lst **cmd_lst);
t_cmd_lst	*cmd_last(t_cmd_lst *cmd_lst);
t_cmd_lst	*cmd_new(const char *cmd);
size_t		cmd_size(t_cmd_lst *cmd_lst);

int		ft_parser(char *input);
int		ft_lexer(char *input);
void	minishell_signal(void);

#endif
