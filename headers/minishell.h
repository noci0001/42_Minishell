/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:13:46 by snocita           #+#    #+#             */
/*   Updated: 2023/08/06 16:30:09 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//ERROR CODES
# define SUCCESS 0
# define GENERALERROR 1
# define MISUSEOFBUILTINS 2
# define CANNOTEXECUTE 126
# define COMMANDNOTFOUND 127
# define NOPATH "NO ENVP?"

# define UNSET 0
# define EXPORT 1

# define SKIP 1
# define NOSKIP 0

//TO OBTAIN ENVP
# define GET_KEY 0
# define GET_VALUE 1

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define HEREDOC 7
# define END 8

// LIBFT
# include "../libft/libft.h"
// # include "libreadline.h"
# include <readline/readline.h>
# include <readline/history.h>
// readline, rl_clear_history, rl_on_new_line,
//	rl_replace_line, rl_redisplay, add_history
# include <stdio.h>
// printf
# include <stdlib.h>
// malloc, free
# include <unistd.h>
# include <fcntl.h>
// write, access, open, read, close,
//	dup, dup2, pipe, isatty, ttyname,
//	ttyslot, ioctl
# include <sys/types.h>
// fork, wait, waitpid, wait3, wait4
# include <signal.h>
// kill, exit
# include <sys/stat.h>
// getcwd, chdir, stat, lstat, fstat, unlink,
// errono macro
# include <errno.h>
//	execve
# include <dirent.h>
// opendir, readdir, closedir
# include <string.h>
// strerror, perror
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <sys/wait.h>
// tcsetattr, tcgetattr, tgetent,
//	tgetflag, tgetnum, tgetstr, tgoto, tputs: termios.h

typedef struct s_gen	t_gen;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_token
{
	char			*str;
	int				type;
	int				exp_disabled;
	char			*path;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

struct s_gen
{
	t_token	*start;
	t_env	*env;
	int		exit;
	int		in;
	int		out;
	int		fdin;
	int		fdout;
	int		pipin;
	int		pipout;
	int		pid;
	int		responsibility;
	int		parent;
	int		last;
	int		ret;
	int		no_exec;
	char	*input;
};

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}					t_sig;

extern t_sig			g_sig;

void	reset_fds(t_gen *gen, int ac, char **av);
int		env_init(t_gen *gen, char **envp, int ac, char **av);
void	free_env(t_env *env);
void	increase_shlvl(t_env	*env);
void	sig_init(void);
void	check_input_and_history(t_gen	*gen);
void	parse(char *line, t_gen *gen);
int		quotes(char *line, int index);
char	*space_line(char *line);
t_token	*get_tokens(char *line);
int		is_type(t_token *token, int type);
int		is_types(t_token *token, char *types);
int		has_type(t_token *token, int type);
t_token	*next_type(t_token *token, int type, int skip);
int		has_pipe(t_token *token);
t_token	*loop_through_line(char *line, int index);
void	squish_args(t_gen *gen);
void	squish_args2(t_gen *gen, t_token *token, t_token	*prev);
void	type_arg(t_token *token, int separator);
void	expansion_function(t_gen	*gen, t_token	*token);
void	check_expansion(t_gen *gen, t_token *token);
char	*expansion_string(t_gen *gen, char *str, int index);
t_token	*next_sep(t_token *token, int skip);
t_token	*prev_sep(t_token *token, int skip);
t_token	*next_run(t_token *token, int skip);
char	*space_alloc(char *line);
void	ft_skip_space(const char *str, int *i);
int		ignore_sep(char *line, int i);
t_token	*next_token(char *line, int *i);
int		is_last_valid_arg(t_token *token);
int		next_alloc(char *line, int *i);
t_env	*is_inside_envp(t_env *envp, t_gen *gen, int check, char	*str);
int		check_line(t_gen *gen, t_token *token);
void	execution(t_gen *gen);
int		unexpected_token_message(t_token	*token, t_gen	*gen, int version);
void	ft_close(int fd);
void	reset_std(t_gen *gen);
void	close_fds(t_gen *gen);
void	free_token(t_token *start);
void	redir(t_gen *gen, t_token *token, int type);
void	input(t_gen *gen, t_token *token);
void	here_doc(t_gen *gen, t_token *token);
void	here_doc2(t_gen	*gen, t_token *token);
void	redirection_handler(t_gen *gen, t_token *token);
int		cmdpipe(t_gen *gen);
void	free_tab(char **tab);
char	**cmd_tab(t_token *start);
char	**cmd_tab_continue(char **tab, t_token *token, t_token *start);
void	program_exit(t_gen *gen, char **cmd_array);
int		is_builtin(t_gen	*gen);
int		do_builtin(t_gen	*gen);
int		error_message(char *path);
int		magic_box(char *path, char **args, t_env *env, t_gen *gen);
char	*path_join(const char *s1, const char *s2);
char	*check_dir(char *bin, char *command);
int		exec_bin(char **args, t_env *env, t_gen *gen);
int		check_splitted_env(t_gen *gen, char **splitted_env);
int		cmd_validation(t_gen	*gen);
int		free_env_list2(t_env *env);
int		check_for_tail(t_gen	*gen, t_env	*tail);
int		look_for_head(t_gen	*node, t_env *env);
void	get_home_path(char **envp, t_env	*new);
void	register_key_values(t_env	*new, char **envp, int i);
void	evaluate_strings_and_exit_code(t_token	*token, t_gen	*gen);
int		go_execute(t_gen *gen, t_env *env, char *path, char **args);
int		allocate_bin(char **bin, t_env	*env, char **args);
int		execute_depending_on_path(char	*path, char **args,	\
		t_env *env, t_gen *gen);
int		navigate_until_path(t_env	*env);
int		is_match(t_env	*env);
int		continue_execution(t_env *env, char **args, t_gen *gen);
int		ft_clear(void);
//BUILTINS
//CD 
int		navigate_backward(t_env	*env);
int		navigate_forward(t_env	*env, char	*arg);
int		navigate_home(t_env	*env, int is_tilde, t_gen	*gen);
int		go_places(char	*arg, t_env	*env);
int		ft_cd(t_gen	*gen, t_env	*env);
void	update_oldpwd(t_env	*env, char	*old_cwd);
int		update_pwd(t_env	*env);
char	*ft_get_env(t_env *env, char *value_to_fetch);
int		is_arg_absent(t_gen	*gen, t_env	*envp, int check);
int		go_to_path(t_env *env);
char	*get_old_pwd(t_env	*env);
//ECHO
int		loop_through_tokens(t_token *token, int *print_new_line);
int		ft_echo(t_token *token, t_gen *gen, t_env *env);
//ENV
void	add_key_value(t_env	*env);
int		obtain_envp(t_gen *gen, char **envp);
char	*env_to_str_func(t_env *lst);
int		ft_env(t_env *env);
int		free_env_list(t_env *env);
char	*get_str_home_path(char **envp);
int		check_for_path(t_env	*env);
//EXPORT
char	*get_value_from_before_equal(char	*str, int index);
char	*get_value_before_equal(char *str);
t_env	*is_inside_envp(t_env *envp, t_gen *gen, int check, char	*str);
int		add_node_to_envp(t_env *envp, t_gen	*gen);
int		look_for_head_for_export(char *key, t_env *env);
void	continue_export(t_env *envp, t_gen *gen, char *key);
//EXPORT
int		ft_export(t_gen *gen, t_env *envp);
void	free_and_add_node(char	*key, t_env *envp, t_gen *gen);
void	free_and_replace_value(t_env	*envp, t_gen	*gen, char	*key);
int		check_for_arg_absence_or_head(t_gen	*gen, t_env	*envp);
//UNSET
int		ft_unset(t_gen *gen, t_env *env);
void	remove_middle_man_found_inbetween(t_env	*env);
void	remove_middle_man(t_env	*env);
//PWD
int		ft_pwd(t_env	*env);
int		absent_or_not(t_gen	*gen, t_env	*env);
size_t	size_env(t_env *lst);
void	free_head(t_gen	*gen);
void	signal_handler_ctrl_c(int signal);
void	rl_clear_history(void);
void	rl_replace_line(const char *text, int clear_undo);
void	turn_off_echo(void);

#endif