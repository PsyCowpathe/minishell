/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redirin_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:47:48 by agirona           #+#    #+#             */
/*   Updated: 2022/02/10 18:48:50 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_in	*redirnew(char *str)
{
	t_redir_in	*new;

	if (new_malloc((void *)&new, sizeof(t_redir_in), 1) == 0)
		return (NULL);
	new->str = str;
	new->key = NULL;
	new->value = NULL;
	new->set = 1;
	new->next = NULL;
	return (new);
}

t_redir_in	*envlast(t_redir_in *lst)
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

void	envadd_back(t_redir_in **alst, t_redir_in *new)
{
	t_redir_in	*last;

	if (!*alst)
		*alst = new;
	else
	{
		last = envlast(*alst);
		last->next = new;
	}
}

void	envclear(t_redir_in **lst)
{
	t_redir_in	*next;

	while (*lst)
	{
		next = (*lst)->next;
		if ((*lst)->key)
			free((*lst)->str);
		if ((*lst)->key)
			free((*lst)->key);
		if ((*lst)->value)
			free((*lst)->value);
		free(*lst);
		*lst = next;
	}
}
