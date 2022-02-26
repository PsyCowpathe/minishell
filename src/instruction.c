/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:28:37 by agirona           #+#    #+#             */
/*   Updated: 2022/02/25 23:08:13 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cut_instruction(t_inst *inst, t_env *env)
{
	int		i;
	char	*command;

	i = 0;
	while (inst->str && inst->str[i])
	{
		while (inst->str[i] && ft_iswhitespace(inst->str[i]) == 1)
			i++;
		if (cpy_size_to_char(&command, inst->str, &i, "|") != 1)
			return (-1);
		cmdadd_back(&inst->cmds, cmdnew(ft_strdup(command), env));
		free(command);
		if (inst->str[i] == '|')
			i++;
		cut_command(cmdlast(inst->cmds));
	}
	return (1);
}
