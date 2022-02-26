/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:28:37 by agirona           #+#    #+#             */
/*   Updated: 2022/02/26 22:28:11 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cut_instruction(t_inst *inst, t_env *env)
{
	int		i;
	char	*command;
	int		ret;
	char	*tmp;
	t_cmd	*ctmp;

	i = 0;
	while (inst->str && inst->str[i])
	{
		while (inst->str[i] && ft_iswhitespace(inst->str[i]) == 1)
			i++;
		ret = cpy_size_to_char(&command, inst->str, &i, "|"); 
		if (ret == -1)
			return (return_perror(-1, "error ", ENOMEM));
		if (ret == 0)
			return (0);
		tmp = ft_strdup(command);
		if (tmp == NULL)
		{
			free(command);
			return (return_perror(-1, "error ", ENOMEM));
		}
		ctmp = cmdnew(tmp, env);
		if (ctmp == NULL)
		{
			free(tmp);
			free(command);
			return (return_perror(-1, "error ", ENOMEM));
		}
		cmdadd_back(&inst->cmds, ctmp);
		free(command);
		if (inst->str[i] == '|')
			i++;
		ret = cut_command(cmdlast(inst->cmds));
		if (ret == -1)
			return (-1);
		if (ret == 0)
			return (0);
	}
	return (1);
}
