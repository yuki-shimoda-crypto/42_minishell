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

// tokenize.c
#define SINGLE_QUOTE_CHAR '\''
#define DOUBLE_QUOTE_CHAR '"'

typedef enum e_token_kind	t_token_kind;
enum e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
};

typedef struct s_token		t_token;
struct s_token
{
	char			*word;
	t_token_kind	kind;
	t_token			*next;
};

t_token	*tokenize(char *line);
char	**token_list_to_argv(t_token *tok);
bool	is_operator(const char *s);
bool	is_metacharacter(char c);


// destructor.c
void	free_tok(t_token *tok);
void	free_argv(char **argv);

// error.c
# define ERROR_TOKENIZE 258
extern bool	syntax_error;
void	assert_error(const char *msg);
void	err_exit(const char *location, const char *msg, int status);
void	fatal_error(const char *msg);
void	todo(const char *msg);
void	tokenize_error(const char *location, char **rest, char *line);

// expand.c
void	expand(t_token *tok);

// libft
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);


# endif

