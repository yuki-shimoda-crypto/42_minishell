/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:53:27 by yshimoda          #+#    #+#             */
/*   Updated: 2022/12/14 23:47:09 by yshimoda         ###   ########.fr       */
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
	char			*cmd;
	char			**cmd_option;
	char			**redirections;
	size_t			*s_quote_flag;
	size_t			*d_quote_flag;
	int				output_redirection;
	pid_t			pid;
	struct s_cmd	*next;
}		t_cmd;

int		ft_parser(char *input);
int		ft_lexer(char *input);
void	minishell_signal(void);

#endif
