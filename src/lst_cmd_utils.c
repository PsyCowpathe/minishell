/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:49:26 by agirona           #+#    #+#             */
/*   Updated: 2021/11/30 15:35:58 by agirona          ###   ########lyon.fr   */
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
	new->ret[0] = 0;
	new->builtin = 0;
	new->str = content;
	new->exec = NULL;
	new->echo_flag = 0;
	new->args = NULL;
	new->next = NULL;
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
