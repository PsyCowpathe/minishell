/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:30 by agirona           #+#    #+#             */
/*   Updated: 2021/11/24 20:23:00 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <readline/readline.h>

typedef struct s_cmd
{
	char			*str;
	char			*exec;
	int				flag;
	char			**args;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_inst
{
	char	*str;
	t_cmd	*cmds;
	struct s_inst	*next;
}				t_inst;

// lst_inst_utils

t_inst	*instnew(char *content);
void	instadd_back(t_inst **alst, t_inst *new);
void	instclear(t_inst **lst);
t_inst	*instlast(t_inst *lst);

// lst_cmd_utils

t_cmd	*cmdnew(char *content);
void	cmdadd_back(t_cmd **alst, t_cmd *new);
void	cmdclear(t_cmd **lst);
t_cmd	*cmdlast(t_cmd *lst);

#endif
