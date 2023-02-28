/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:36:34 by yshimoda          #+#    #+#             */
/*   Updated: 2023/02/22 09:02:53 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEll_H
# define MINISHEll_H

# include <stdbool.h>
# include <stddef.h>

# define LINUX

# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'

typedef enum e_token_kind	t_token_kind;
typedef struct s_token		t_token;
typedef enum e_node_kind	t_node_kind;
typedef struct s_node		t_node;

// error.c
extern bool	syntax_error;
void	assert_error(const char *msg) __attribute__((noreturn));
void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));
void	fatal_error(const char *msg) __attribute__((noreturn));
void	todo(const char *msg) __attribute__((noreturn));
void	tokenize_error(const char *location, char **rest, char *line);
void	parse_error(const char *location, t_token **rest, t_token *tok);
void	xperror(const char *location);

// tokenize.c
enum e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
};

struct s_token
{
	char			*word;
	t_token_kind	kind;
	t_token			*next;
};

enum e_node_kind
{
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
};

struct s_node
{
	t_node_kind	kind;
	t_node		*next;
	// CMD
	t_token		*args;
	t_node		*redirects;
	// REDIR
	int			targetfd;
	t_token		*filename;
	int			filefd;
	int			stashed_targetfd;
};

t_token	*tokenize(char *line);
char	**token_list_to_argv(t_token *tok);
bool	is_operator(const char *s);
bool	is_metacharacter(char c);
t_token	*new_token(char *word, t_token_kind kind);


// destructor.c
void	free_node(t_node *node);
void	free_tok(t_token *tok);
void	free_argv(char **argv);


// expand.c
void	expand(t_node *node);

// parse.c
t_node	*parse(t_token *tok);
t_node	*redirect_out(t_token **rest, t_token *tok);
void	append_command_element(t_node *command, t_token **rest, t_token *tok);
bool	at_eof(t_token *tok);
bool	equal_op(t_token *tok, char *op);
t_node	*new_node(t_node_kind kind);
t_token	*tokdup(t_token *tok);
void	append_tok(t_token **tok, t_token *elm);
void	append_node(t_node **node, t_node *elm);

// redirect.c
void	open_redir_file(t_node *redirects);
void	do_redirect(t_node *redirects);
void	reset_redirect(t_node *redirects);

// libft
#ifdef LINUX
size_t	strlcat(char *dst, const char *src, size_t dstsize);
size_t	strlcpy(char *dst, const char *src, size_t dstsize);
#endif



# endif


