/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redirin_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:47:48 by agirona           #+#    #+#             */
/*   Updated: 2022/02/27 05:10:47 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
