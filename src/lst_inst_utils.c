/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:49:26 by agirona           #+#    #+#             */
/*   Updated: 2021/11/24 20:22:55 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_inst	*instnew(char *content)
{
	t_inst	*new;

	if (new_malloc((void *)&new, sizeof(t_inst), 1) == 0)
		return (NULL);
	new->str = content;
	new->cmds = NULL;
	new->next = NULL;
	return (new);
}

t_inst	*instlast(t_inst *lst)
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

void	instadd_back(t_inst **alst, t_inst *new)
{
	t_inst	*last;

	if (!*alst)
		*alst = new;
	else
	{
		last = instlast(*alst);
		last->next = new;
	}
}

void	instclear(t_inst **lst)
{
	t_inst	*next;

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
