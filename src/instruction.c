/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:28:37 by agirona           #+#    #+#             */
/*   Updated: 2021/12/16 16:15:31 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cut_instruction(t_inst *inst)
{
	int		i;
	char	*command;

	i = 0;
	while (inst->str[i])
	{
		while (inst->str[i] && ft_iswhitespace(inst->str[i]) == 1)
			i++;
		if (cpy_size_to_char(&command, inst->str, &i, "|") != 1)
			return ;
		cmdadd_back(&inst->cmds, cmdnew(ft_strdup(command)));
		free(command);
		if (inst->str[i] == '|')
			i++;
		cut_command(cmdlast(inst->cmds));
	}
}
