/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:30 by agirona           #+#    #+#             */
/*   Updated: 2021/11/23 18:47:07 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft.h"
# include <readline/readline.h>

typedef struct s_inst
{
	char	*str;
	//t_cmd	*cmds
	struct s_inst	*next;
}				t_inst;

// lst_utils

t_inst	*instnew(char *content);
void	instadd_back(t_inst **alst, t_inst *new);
void	instclear(t_inst **lst);


#endif
