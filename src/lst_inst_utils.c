/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_inst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:49:26 by agirona           #+#    #+#             */
/*   Updated: 2022/02/26 18:03:14 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_inst	*instnew(char *content)
{
	t_inst	*new;

	if (new_malloc((void *)&new, sizeof(t_inst), 1) == 0)
	{
		return_perror(-1, "error ", ENOMEM);
		return (NULL);
	}
	new->str = content;
	new->cmds = NULL;
	return (new);
}

void	instclear(t_inst *inst)
{
	t_cmd	*next;

	if (inst)
	{
		if (inst->str)
			free(inst->str);
		while (inst->cmds)
		{
			next = inst->cmds->next;
			cmd_clear(inst->cmds);
			inst->cmds = next;
		}
		free(inst);
	}
}
