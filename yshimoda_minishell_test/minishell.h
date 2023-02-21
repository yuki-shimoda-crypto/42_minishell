/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:36:34 by yshimoda          #+#    #+#             */
/*   Updated: 2023/02/21 17:03:54 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEll_H
# define MINISHEll_H

# include <stdbool.h>

typedef struct s_token		t_token;
typedef enum e_token_kind	t_token_kind;

struct s_token
{
	char			*word;
	t_token_kind	kind;
	t_token			*next;
};

enum e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
};

// error.c
void	err_exit(const char *location, const char *msg, int status);
void	fatal_error(const char *msg);


# endif
