/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:08:25 by ppolinta          #+#    #+#             */
/*   Updated: 2025/03/05 13:32:56 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\x1b[0;37m"
# define BOLD		"\x1b[1m"
# define RESET		"\x1b[0m"
# define SHELLNAME	"cerith: "
# define SHELLPRMPT	"[cerith] "

/* GLOBAL VARIABLE FOR SIGNAL */
extern int	g_sig;

/* FLAGS FOR TOKEN TYPES */
enum e_type
{
	CMD = 0,
	PARAM = 1,
	PIPE = 2,
	FILENAME = 3,
	INF = 4,
	OUTF = 5,
	OUTF_APD = 6,
	HERE_DOC = 7,
	LIMITER = 8,
	UNKNOWN = 9,
	NA = -1
};

/* DOUBLY LINKED LIST STRUCTURE */
typedef struct s_dlist
{
	char			*str;
	enum e_type		token;
	int				index;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

/* MAIN DATA STRUCTURE */
typedef struct s_data
{
	t_dlist	*env;
	char	*input;
	t_dlist	*tokens;
	char	**instructions;
	int		*in_fds;
	int		*out_fds;
	pid_t	*pids;
	int		cmd_count;
	int		exit_status;
	int		pipe_fds[2];
	int		prev_pipe_fd;
	int		open_fail;
}	t_data;

/* MAIN */
void	reset_data(t_data *data);

/* SIGNALS */
void	readline_sig(int sig);
void	do_nothing(int sig);
void	hdc_sig(int sig);

/* TAKE INPUT */
void	take_input(t_data *data);
void	reset_input(t_data *data);

/* PARSE INPUT */
int		parse_input(t_data *data);
int		check_empty_input(char *input);
int		check_quotes(char *input);

/* FIX INPUT AND EXPAND ENV VARS */
char	*fix_input(char *input, t_data *data);
void	copy_full_word(char *input, char *str, size_t *a, size_t *b);
int		check_invalid_chars_env_var(char c);
void	expand_all_tokens(t_data *data);
char	*expand_env_vars(char *str, t_data *data);
size_t	get_exp_len(char *str, t_data *data);
void	get_exp_len_extension(char *str, t_data *data, size_t *len);
char	*get_env_var_str(char *str, t_data *data);
void	skip_single_quotes(char *str, int *dquote, int *squote, size_t *i);
void	set_squotes_flag(char *str, int *squote, int *dquote, size_t *i);
void	set_dquotes_flag(char *str, int *dquote, int *squote, size_t *i);
size_t	env_var_name_len(char *str);
void	remove_quotes(t_data *data);
char	*remove_quotes_extension(char *str, t_data *data);

/* EXECUTION */
void	execution(t_data *data);
void	exec_single_cmd(t_data *data, int n);
void	execve_fail(char *cmd, char **execve_arr, char **env, t_data *data);
void	open_files(t_data *data, t_dlist *node, int n);
void	open_files_extension(t_data *data, int in_fd, int out_fd, int n);

/* EXECUTION UTILS */
void	alloc_fd_pid_arrays(t_data *data);
char	*get_file(char *instruction);
void	convert_tokens(t_data *data);
char	**create_exec_array(t_data *data, int n);
int		open_infile(t_data *data, t_dlist *node, int in_fd);
int		open_outfile(t_data *data, t_dlist *node, int out_fd, int apd);
void	open_error(t_data *data, int in_fd, int out_fd, int n);
void	close_error(int fd, t_data *data);
void	exit_status(pid_t pid, t_data *data);

/* REDIRECTION */
void	dupdup(t_data *data, int n);
int		dup_close(int oldfd, int newfd, t_data *data);

/* HERE_DOC */
void	open_here_docs(t_data *data, t_dlist *node, int n);
int		here_doc(t_data *data, t_dlist *node);
void	hdc_child(t_data *data, t_dlist *node);
void	exit_here_doc_check(t_data *data, char *limiter, char *line);
int		hdc_check(t_dlist *node, int n);

/* ENV */
void	create_env(t_data *data, char **env);
char	**convert_env_to_strings(t_data *data);
char	*find_path_in_env(char **env);
char	*search_path(char *cmd, char **env, t_data *data);
t_dlist	*get_env_var(char *var, t_dlist *env);
void	update_shlvl(t_dlist *env, t_data *data);
void	update_pwd(t_dlist *env, t_data *data);
void	update_oldpwd(t_dlist *env, t_data *data);
void	add_to_env(char *str, t_data *data);

/* TOKENIZATION */
void	create_token_list(char *input, t_data *data);
char	*get_word(char *input, size_t *i, t_data *data);
void	set_types(t_dlist **tokens);
void	set_types_extension(t_dlist *temp);
int		parse_tokens(t_data *data);
int		check_token_redir(t_dlist *node);
int		check_for_cmd(t_dlist *node);
int		check_token_valid_char(char c);

/* BUILTINS */
int		is_builtin(t_data *data, int n);
void	exec_builtin(t_data *data, int n);
void	exec_single_builtin(t_data *data);
void	builtin_exit(t_data *data, int exit_status);
void	exit_builtin(t_data *data, int n);
void	exit_builtin_no_params(t_data *data, char **params);
void	exit_builtin_invalid_params(t_data *data, char **params);
void	env_builtin(t_data *data);
void	unset_builtin(t_data *data, int n);
void	pwd_builtin(t_data *data);
void	echo_builtin(t_data *data, int n);
size_t	echo_newline_flag(char **params, int *newline);
void	cd_builtin(t_data *data, int n);
void	cd_builtin_extension(char **params, char *dir, t_data *data);
void	export_builtin(t_data *data, int n);
int		export_builtin_extension(char *str, t_data *data);
void	export_builtin_list(t_data *data);
void	sort_export_list(char **export_arr);
void	print_export_list(char **export_arr, int fd);

/* LINKED LIST */
t_dlist	*newnode(char *str);
void	node_addfront(t_dlist **list, t_dlist *node);
void	node_addback(t_dlist **list, t_dlist *new);
t_dlist	*lastnode(t_dlist *list);
int		listsize(t_dlist *list);
void	refreshindex(t_dlist **list);
void	freelist(t_dlist *list);
t_dlist	*skip_instructions(t_dlist *node, int n);

/* GENERAL UTILS */
int		error(char *str, char *token, t_data *data);
void	check_memory_failure(t_data *data, void *ptr, char **dptr, int f);
void	ms_perror(t_data *data);
void	free_all(t_data *data);
void	free_str_array(char **arr, size_t n);
char	*ms_strjoin(char *s1, char *s2, int f, t_data *data);
char	*ms_substr(char const *s, unsigned int start, size_t len, t_data *data);
char	*ms_strdup(const char *s, t_data *data);
int		checkfornum(char *s);
int		cmp_up_to_equal(const char *s1, const char *s2);
int		check_valid_char(int c);
int		check_redir(char *c);
int		is_whitespace(char c);
void	rl_replace_line(const char *text, int clear_undo);

#endif