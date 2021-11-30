/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:28:37 by agirona           #+#    #+#             */
/*   Updated: 2021/11/30 18:27:49 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_instruction(char *dst, char *src, int *start, int size)
{
	int		end;
	int		i;

	end = *start + size;
	i = 0;
	while (*start < end)
	{
		dst[i] = src[*start];
		i++;
		*start = *start + 1;
	}
	dst[i] = '\0';
}

void	cut_instruction(t_inst *inst)
{
	int		i;
	char	*command;
	int		size;

	i = 0;
	while (inst->str[i])
	{
		while (inst->str[i] && ft_iswhitespace(inst->str[i]) == 1)
			i++;
		size = size_to_char(inst->str, i, "|");
		if (size == -1)
			return ;
		if (new_malloc((void **)&command, sizeof(char), size + 1) == 0)
			return ;
		cpy_instruction(command, inst->str, &i, size);
		cmdadd_back(&inst->cmds, cmdnew(ft_strdup(command)));
		free(command);
		if (inst->str[i] == '|')
			i++;
		cut_command(cmdlast(inst->cmds));
	}
}
