/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:30 by agirona           #+#    #+#             */
/*   Updated: 2021/12/16 20:29:31 by agirona          ###   ########lyon.fr   */
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

extern char	*const *g_envp;

typedef struct s_cmd
{
	int				is_valid;
	int				*ret;
	int				builtin;
	char			*str;
	char			*exec;
	int				echo_flag;
	char			**args;
	int				fd[2];
	int				redir_type[2];
	int				hdoc_fd;
	char			*redir_in;
	char			*redir_out;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_inst
{
	char	*str;
	t_cmd	*cmds;
}				t_inst;

// instruction

int		cut_instruction(t_inst *inst);

//command

int		cut_command(t_cmd *cmd);

// lst_inst_utils

t_inst	*instnew(char *content);
void	instclear(t_inst *lst);

// lst_cmd_utils

t_cmd	*cmdnew(char *content);
void	cmdadd_back(t_cmd **alst, t_cmd *new);
void	cmdclear(t_cmd **lst);
t_cmd	*cmdlast(t_cmd *lst);

// debug															//ntm

void	print_debug(t_inst *inst);
void	print_env(void);
void	print_path(char **path);

// utility

int		is_closed_quote(char *str, int i);
int		size_to_char(char *input, int i, char *find);
void	cpy_instruction(char *dst, char *src, int *start, int size);
int		cpy_size_to_char(char **dst, char *src, int *start, char *search);

// command_utiliy

int	is_builtin(t_cmd *cmd);
int	count_args(char	*str, int i);
int	strcmp_quote(char *str, char *find);

// builtin

void	exec_echo(t_cmd *cmd);

// path

char	**get_path(void);
char	*join_path(char *exec, char *path);
void	exec_lonely_path(t_cmd *cmd);
int		exec_path(t_cmd *cmd);

//redirection

int		cut_redir(t_cmd *cmd, int *i);

//open

int	verif_open(t_cmd *cmd, char *fragment, int redir_type);

//input_output

int		create_output_redirection(t_cmd *cmd);
int		create_input_redirection(t_cmd *cmd);

//exec

void	exec_pipe(t_cmd	*cmd);
void	exec_lonely(t_cmd *cmd);

//child

void	first_child(t_cmd *cmd);
void	last_child(t_cmd *cmd);
void	perfect_child(t_cmd *cmd);

#endif
