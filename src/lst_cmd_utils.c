/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:49:26 by agirona           #+#    #+#             */
/*   Updated: 2022/02/27 04:39:56 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmdnew(char *content, t_env *env)
{
	t_cmd	*new;

	if (new_malloc((void *)&new, sizeof(t_cmd), 1) == 0)
		return (NULL);
	new->ret = malloc(4);
	if (new->ret == NULL)
		return (NULL);
	new->ret[0] = 0;
	new->builtin = 0;
	new->str = content;
	new->exec = NULL;
	new->is_path = 0;
	new->echo_flag = 0;
	new->args = NULL;
	new->redir_type[0] = 0;
	new->redir_type[1] = 0;
	new->redir_in = NULL;
	new->redir_out = NULL;
	new->hdoc_fd = -1;
	new->next = NULL;
	new->prev = NULL;
	new->fd[0] = -1;
	new->fd[1] = -1;
	new->env = env;
	return (new);
}

t_cmd	*cmdlast(t_cmd *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
		{
			lst = lst->next;
		}
	}
	return (lst);
}

void	cmdadd_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*last;

	if (!*alst)
		*alst = new;
	else
	{
		last = cmdlast(*alst);
		last->next = new;
		new->prev = last;
	}
}
