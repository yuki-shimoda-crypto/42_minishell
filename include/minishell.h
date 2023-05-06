/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:11:08 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/07 02:45:11 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// prompt name
# define PROMPT			"\x1b[1m\x1b[32mminishell\x1b[0m$ "
# define PROMPT_ERROR	"minishell: "

// error
# define ERROR_ASSERT	"minishell: assert error "
# define ERROR_EXEC		"minishell: "
# define ERROR_SYNTAX	"minishell: syntax error near unexpected token "
# define ERROR_EXPORT	"minishell: export: `%s': not a valid identifier\n"

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
	bool		quote_flag;
	// PIPE
	int			fd_save_inpipe;
	int			fd_save_outpipe;
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
	bool	redirect_error;
	bool	exec_error;
	int		g_sig;
	int		return_value;
	//fix
	bool	export_error;
	bool	heredoc_interupt;
	bool	ctrl_c;//
};

extern t_return_error	g_return_error;

// main.c
void	ctrl_c(int sig);
void	free_token(t_tk **token);
void	free_node(t_node **node);

//signal
void	ctrl_backslash(int sig);
void	ctrl_c(int sig);
int		signal_hook(void);
void	setup_signal(void);

// error.c
void	assert_error(const char *msg);
void	syntax_error(const char *msg, char **skipped, char *line);
void	file_exec_error(const char *word, const char *msg);
int		export_error(const char *cmd);
void	env_error(const char *cmd);
int		unset_error(const char *cmd);
void	exit_numeric(const char *cmd);
void	cd_error(const char *cmd);


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
bool	is_relative_path(const char *word);
char	*find_env_path(t_env *env_list);
char	*make_absolute_path(t_tk *token);
char	*make_environment_path(t_tk *token, t_env *env_list);
char	*make_pathname(t_tk *token, t_env *env_list);
size_t	argv_len(t_tk *token);
char	**make_argv(t_tk *token);
void	exec(char *pathname, char **argv, char **envp, t_node *node);
void	exec_cmd(t_node *node, t_env **env_list);
void	wait_child_process(void);

// redirect.c
int		open_redir_file(t_node *redir, t_env *env_list);
void	redirect_fd_list(t_node *node, t_env *env_list);
void	do_redirect(t_node *redird);
void	reset_redirect(t_node *redir);
int		heredoc(char *delimiter, t_env *env_list, bool quote_flag);
int		open_redir_out(char *filename);
int		open_redir_append(char *filename);
int		open_redir_in(char *filename);

// pipe.c
void	input_pipefd(t_node *node, int *inpipe);
void	connect_pipe(t_node *node);
void	reset_pipe_builtin(t_node *node);
void	connect_pipe_builtin(t_node *node);
bool	is_redirect_in_exist(t_node *node);
bool	is_redirect_out_exist(t_node *node);

// wrap
int		wrap_close(int fd);
int		wrap_dup(int oldfd);
int		wrap_dup2(int oldfd, int newfd);
pid_t	wrap_fork(void);
int		wrap_pipe(int pipefd[2]);
ssize_t	wrap_read(int fd, void *buf, size_t count);
ssize_t wrap_write(int fd, const void *buf, size_t count);
char	*wrap_getcwd(char *buf, size_t size);
int		wrap_chdir(const char *path);

// expand
void	expand(t_node *node, t_env *env_list);
bool	is_single_quote(const char c);
bool	is_double_quote(const char c);
bool	is_variable(char *line);
bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);
bool	is_special_charactor(char *line);
char	*expand_word(char *word, t_node_kind kind, t_env *env_list);
char	*expand_special_char(char **skipped, char *word, char *new_word);
char	*expand_variable(char **skipped, char *word, char *new_word, t_env *env_list);
char	*expand_db_quote(char **skipped, char *word, char *new_word, t_env *env_list);
char	*expand_single_quote(char **skipped, char *word, char *new_word);
char	*append_char(char **skipped, char *word, char *new_word);
t_env	*find_word_expandable(const char *key, t_env *env_list);
char	*make_expanded_word(char *new_word, t_env *target_list);
char	*make_new_word(char *head, char *word, char *append_word, char *new_word);

//builtin
int		builtin_echo(char **argv);
int		builtin_export(char **argv, t_env **env_list);

int		recognize_builtin(char **argv, t_env **env_list, bool one_cmd);
bool	is_builtin(const char *cmd);
int		builtin_pwd(void);
int		builtin_cd(char **destination, t_env **env_list);
int		rewrite(char *old_pwd, t_env **env_list);
int		rewrite_go_back(char *old_pwd, t_env **env_list, t_env *path);
void	join_add_env(char *key, char *value, t_env **env_list);
int		builtin_env(t_env *env_list);
int		builtin_unset(char **del_target, t_env **env_list);
int		builtin_exit(char **argv, bool one_cmd);
void	free_array(char **env_array);
void	sort_array(char **env_array);
char	**env_into_array(t_env *env_list);
bool	is_key_exist(const char *env, t_env *env_list);

// env
t_env	*search_env(const char *key, t_env *env_list);
void	del_env(const char *key, t_env **env_list);
t_env	*env_last(t_env *env_list);
void	env_addback(t_env **env_list, t_env *env_new);
void	free_env(t_env **env_list);
t_env	*env_new(char *key, char *value);
void	add_env(const char *env, t_env **env_list);
t_env	*make_env_list(char **envp);
t_env	*env_new(char *key, char *value);
t_env	*env_last(t_env *env_list);
void	env_addback(t_env **env_list, t_env *env_new);


// debug_func.c
void	print_t_tk(t_tk	*token);
void	print_node(t_node *node, int i);
void	print_env_list(t_env *env_list);

char	*itoa(int n);

#endif
