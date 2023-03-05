/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:11:08 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/04 20:24:41 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef minishell_h
#define minishell_h

# include <stdbool.h>
# include <stdint.h>

typedef enum	e_tk_kind t_tk_kind;
typedef struct	s_tk t_tk;
typedef enum	e_node_kind t_node_kind;
typedef struct	s_node t_node;
typedef struct	s_env t_env;

enum e_tk_kind
{
    TK_WORD,
    TK_OPERATOR,
    TK_EOF,
};

struct s_tk
{
    char			*word;
	t_tk_kind		kind;
    struct s_token	*next;
};

enum e_node_kind
{
    ND_PIPE,
    ND_SIMPLE_CMD,
    ND_REDIRECT_OUT,
    ND_REDIRECT_IN,
    ND_REDIRECT_APPEND,
    ND_REDIRECT_HEREDOC,
};

struct s_node
{
	t_node_kind	kind;
    t_node		*next;
    // CMD
	t_node	*command;
    // REDIRECT
	t_node	*redirect;
	t_tk	*filename;
	t_tk	*delimiter;
	int		filefd;
};

struct s_env
{
	char		*key;
	char		*value;
	t_env		*pre;
	t_env		*next;
};

#endif
