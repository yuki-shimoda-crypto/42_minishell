/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:11:08 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/07 00:27:49 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef minishell_h
#define minishell_h

# include <stdbool.h>
# include <stdint.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum	e_tk_kind t_tk_kind;
typedef struct	s_tk t_tk;
typedef enum	e_node_kind t_node_kind;
typedef struct	s_node t_node;
typedef struct	s_env t_env;
typedef struct	s_return_error t_return_error;

enum e_tk_kind
{
    TK_WORD,
    TK_REDIRECT,
    TK_PIPE,
    TK_EOF,
};

struct s_tk
{
    char			*word;
	t_tk_kind		kind;
    t_tk			*next;
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

struct s_return_error
{
    bool    tokenize_error;
    bool    parse_error;
    int     return_value;
};

extern t_return_error   g_return_error;

// error.c
void	assert_error(const char *msg);
void	syntax_error(const char *msg, char **skipped, char *line);

// debug_func.c
void	print_t_tk(t_tk	*token);

// tokenize.c
t_tk	*pipe_into_list(char **skipped, char *line, t_tk *token);
t_tk	*word_into_list(char **skipped, char *line);
t_tk	*redirect_into_list(char **skipped, char *line, const char c, t_tk *token);
t_tk	*quoted_into_list(char **skipped, char *line, const char c);
t_tk	*token_new(char *word, t_tk_kind kind);
t_tk	*tokenize(char *line);
void	skip_blank(char **skipped, char *line);

// is.c
bool	is_blank(char c);
bool	is_quote(char c);
bool	is_quoted(char c, char *line);
bool	is_redirect_error(char *line);
bool	is_redirect(char c, char **skipped, char *line);
bool	is_pipe(char c);

#endif
