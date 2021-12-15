/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:49:26 by agirona           #+#    #+#             */
/*   Updated: 2021/12/15 17:13:17 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmdnew(char *content)
{
	t_cmd	*new;

	if (new_malloc((void *)&new, sizeof(t_cmd), 1) == 0)
		return (NULL);
	new->ret = malloc(4);
	if (new->ret == NULL)
		return (NULL);
	new->is_valid = 0;
	new->ret[0] = 0;
	new->builtin = 0;
	new->str = content;
	new->exec = NULL;
	new->echo_flag = 0;
	new->args = NULL;
	new->redir_type[0] = 0;
	new->redir_type[1] = 0;
	new->redir_in = NULL;
	new->redir_out = NULL;
	new->next = NULL;
	new->prev = NULL;
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

void	cmdclear(t_cmd **lst)
{
	t_cmd	*next;

	while (*lst)
	{
		next = (*lst)->next;
		if ((*lst)->str)
			free((*lst)->str);
		//if (*lst->cmds)
			// a free
		free(*lst);
		*lst = next;
	}
}
