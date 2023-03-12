/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:11:08 by yshimoda          #+#    #+#             */
/*   Updated: 2023/03/12 20:31:03 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// prompt name
# define PROMPT			"\x1b[1m\x1b[32mminishell\x1b[0m$ "

// error
# define ERROR_ASSERT	"minishell: assert error "
# define ERROR_EXEC		"minishell: "
# define ERROR_SYNTAX	"minishell: syntax error near unexpected token "

# include <stdbool.h>
# include <stdint.h>

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_tk_kind			t_tk_kind;
typedef struct s_tk				t_tk;
typedef enum e_node_kind		t_node_kind;
typedef struct s_node			t_node;
typedef struct s_env			t_env;
typedef struct s_return_error	t_return_error;

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
	ND_SIMPLE_CMD,
	ND_REDIRECT_OUT,
	ND_REDIRECT_IN,
	ND_REDIRECT_APPEND,
	ND_REDIRECT_HEREDOC,
	ND_PIPE,
};

struct s_node
{
	t_node_kind	kind;
	// CMD
	t_tk		*token;
	// REDIRECT
	t_node		*redirect;
	t_node		*redirect_pre;
	char		*filename;
	int			fd_file;
	int			fd_save;
	int			fd_target;
	// PIPE
	int			inpipe[2];
	int			outpipe[2];
	t_node		*pipe;
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
	bool	tokenize_error;
	bool	parse_error;
	bool	exec_error;
	int		return_value;
};

extern t_return_error	g_return_error;

// error.c
void	assert_error(const char *msg);
void	syntax_error(const char *msg, char **skipped, char *line);
void	file_exec_error(const char *word, const char *msg);

// debug_func.c
void	print_t_tk(t_tk	*token);
void	print_node(t_node *node, int i);

// tokenize.c
t_tk	*pipe_into_list(char **skipped, char *line, t_tk *token);
t_tk	*word_into_list(char **skipped, char *line);
t_tk	*redirect_into_list(char **skipped,
			char *line, const char c, t_tk *token);
t_tk	*quoted_into_list(char **skipped, char *line, const char c);
t_tk	*token_new(char *word, t_tk_kind kind);
t_tk	*tokenize(char *line);

// is.c
bool	is_blank(char c);
bool	is_quote(char c);
bool	is_quoted(char c, char **skipped, char *line);
bool	is_redirect(char c, char **skipped, char *line);
bool	is_pipe(char c);

// parse.c
void	new_node_redirect(t_node *node, t_tk *token);
int		judge_nd_kind(char *redirect);
// t_node	*new_node(t_node_kind kind);
t_node	*new_node(t_node_kind kind, t_node *node_pre);
void	make_redirect(t_node *node, t_tk *token);
t_tk	*dup_token(char *word);
t_tk	*dup_simple_command_token(t_tk **skipped, t_tk *token);
void	make_simple_command(t_node *node, t_tk **skipped, t_tk *token);
t_node	*parse(t_tk *token);

// exec.c
char	*strjoin(char const *s1, char const *s2);
char	*strjoin_three(char const *s1, char const *s2, char const *s3);
bool	is_file_executable(const char *pathname);
bool	is_file_exist(const char *pathname);
bool	is_file(const char *pathname);
char	*find_env_path(char **envp);
char	*make_absolute_path(t_node *node);
char	*make_relative_path(t_node *node, char **envp);
char	*make_pathname(t_node *node, char **envp);
size_t	argv_len(t_tk *token);
char	**make_argv(t_tk *token);
void	exec(char *pathname, char **argv, char **envp, t_node *node);
void	exec_cmd(t_node *node, char **envp);

// redirect.c
int		open_redir_file(t_node *redir);
void	redirect_fd_list(t_node *node);
void	do_redirect(t_node *redir);
void	reset_redirect(t_node *redir);
int		heredoc(char *delimiter);

// pipe.c
void	input_pipefd(t_node *node, int *inpipe);
void	connect_pipe(t_node *node);

// wrap
int		wrap_close(int fd);
int		wrap_dup(int oldfd);
int		wrap_dup2(int oldfd, int newfd);
pid_t	wrap_fork(void);
int		wrap_pipe(int pipefd[2]);
ssize_t wrap_write(int fd, const void *buf, size_t count);

#endif
