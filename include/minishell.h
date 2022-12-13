/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogawa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:53:27 by yshimoda          #+#    #+#             */
/*   Updated: 2022/12/13 13:11:28 by enogawa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include <signal.h>

// # define PROMPT "kimochiiii# "
# define PROMPT "ぎぃぃもちぃぃぃぃいい# "

int		ft_parser(char *input);
int		ft_lexer(char *input);
void	minishell_signal(void);


#endif
