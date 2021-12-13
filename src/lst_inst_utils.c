/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:49:26 by agirona           #+#    #+#             */
/*   Updated: 2021/11/29 17:13:40 by agirona          ###   ########lyon.fr   */
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
	return (new);
}

void	instclear(t_inst *lst)
{
	if (lst)
	{
		if (lst->str)
			free(lst->str);
		//if (*lst->cmds)
			// a free
	}
}
