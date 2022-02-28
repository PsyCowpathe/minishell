/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:30 by agirona           #+#    #+#             */
/*   Updated: 2022/02/28 03:19:21 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>

extern pid_t	g_pid_t[1025];

typedef struct s_env
{
	char			*str;
	char			*key;
	char			*value;
	int				set;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	int				*ret;
	int				builtin;
	char			*str;
	char			*exec;
	int				is_path;
	int				echo_flag;
	char			**args;
	int				fd[2];
	int				redir_type[2];
	int				hdoc_fd;
	char			*redir_in;
	char			*redir_out;
	t_env			*env;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_inst
{
	char	*str;
	t_cmd	*cmds;
}				t_inst;

// instruction

int		cut_instruction(t_inst *inst, t_env *env, int i, int ret);

//command

int		cut_command(t_cmd *cmd, int i, int ret);

// lst_inst_utils

t_inst	*instnew(char *content);
void	instclear(t_inst *lst);

// lst_cmd_utils

t_cmd	*cmdnew(char *content, t_env *env);
void	cmdadd_back(t_cmd **alst, t_cmd *new);
t_cmd	*cmdlast(t_cmd *lst);

// lst_env_utils

t_env	*create_env_lst(char *const envp[]);
t_env	*envnew(char *str);
t_env	*envlast(t_env *lst);
void	envadd_back(t_env **alst, t_env *new);

// utility

int		is_closed_quote(char *str, int i);
int		size_to_char(char *input, int i, char *find);
void	cpy_instruction(char *dst, char *src, int *start, int size);
int		cpy_size_to_char(char **dst, char *src, int *start, char *search);

// command_utiliy

int		is_builtin(t_cmd *cmd);
int		count_args(char	*str, int i);
int		strcmp_quote(char *str, char *find);
int		expand_args(t_cmd *cmd);

// builtin

int		simple_builtin(t_cmd *cmd);

// path

char	**get_path(t_env *env, int i, int d);
void	exec_lonely_path(t_cmd *cmd, char **env_tab);
int		exec_path(t_cmd *cmd);

//redirection

int		cut_redir(t_cmd *cmd, int *i);

//open

int		verif_open(t_cmd *cmd, char *fragment, int redir_type);

//input_output

int		create_output_redirection(t_cmd *cmd);
int		create_input_redirection(t_cmd *cmd);

//exec

int		exec_pipe(t_cmd	*cmd);
int		exec_lonely(t_cmd *cmd);

//exec_utility

int		exec_last_dependency(t_cmd *cmd, pid_t cpid);
char	**exec_lonely_dependency(t_cmd *cmd);

//child

int		first_child(t_cmd *cmd);
int		last_child(t_cmd *cmd);
int		perfect_child(t_cmd *cmd);

//env

char	**build_env_tab(t_cmd *cmd);

//dolar

char	*dollar_expand(char *str, t_env *env, int i, int d);

//dolar_utility

int		search_key(t_env *env, char *key, char **res);
int		trigger(char c, int state);
int		join_all_part(char *res, char **full_res, char *str, int *d);
char	*dollar_expand_return_fucktion(char *full_res, int d);

//quote

void	remove_quotes(char *str);
void	shift(char *str, int i);

//pid

void	set_pid(int pid);
void	init_pid(void);

//signals

int		signals(void);

//error

int		return_error(int ret);
int		return_perror(int ret, char *msg, int code);

//clear

void	envtab_clear(char **env_tab);
void	env_clear(t_env *env);
void	cmd_clear(t_cmd *cmd);
int		instclear_return(t_inst *inst, int ret);

//path_utility

int		path_count(char *str);
char	*join_path(char *exec, char *path);

//args

int		get_args(t_cmd *cmd, int i);

//cd

int		exec_cd(t_cmd *cmd);

//export

int		exec_export(t_cmd *cmd, int i, int ret);

//echo

int		exec_echo(t_cmd *cmd, int i, int fd, int flag);

#endif
