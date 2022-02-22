/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_inst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:49:26 by agirona           #+#    #+#             */
/*   Updated: 2022/02/21 15:30:40 by agoublai         ###   ########lyon.fr   */
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

void	cmd_clear(t_cmd *cmd)
{
	if (cmd->ret)
		free(cmd->ret);
	if (cmd->str)
		free(cmd->str);
	if (cmd->exec)
		free(cmd->exec);
	if (cmd->args)
	{
		int i = 1;
		while (cmd->args[i])
		{
			if (cmd->args[i])
				free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->redir_in)
		free(cmd->redir_in);
	if (cmd->redir_out)
		free(cmd->redir_out);
	free(cmd);
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
