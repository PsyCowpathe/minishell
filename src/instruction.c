/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:28:37 by agirona           #+#    #+#             */
/*   Updated: 2022/02/27 05:10:46 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cut_instruction_dependency(t_inst *inst, t_cmd *ctmp, int *i, char *command)
{
	int		ret;

	cmdadd_back(&inst->cmds, ctmp);
	free(command);
	if (inst->str[*i] == '|')
		(*i)++;
	ret = cut_command(cmdlast(inst->cmds));
	if (ret == -1)
		return (-1);
	if (ret == 0)
		return (0);
	return (1);
}

int	cut_dependency(t_inst *inst, int *i, char **command, char **tmp)
{
	int		ret;

	while (inst->str[*i] && ft_iswhitespace(inst->str[*i]) == 1)
		(*i)++;
	ret = cpy_size_to_char(command, inst->str, i, "|");
	if (ret == -1)
		return (return_perror(-1, "error ", ENOMEM));
	if (ret == 0)
		return (0);
	*tmp = ft_strdup(*command);
	if (*tmp == NULL)
	{
		free(*command);
		return (return_perror(-1, "error ", ENOMEM));
	}
	return (1);
}

int	cut_instruction(t_inst *inst, t_env *env, int i, int ret)
{
	char	*command;
	char	*tmp;
	t_cmd	*ctmp;

	while (inst->str && inst->str[i])
	{
		ret = cut_dependency(inst, &i, &command, &tmp);
		if (ret == -1 || ret == 0)
			return (ret);
		ctmp = cmdnew(tmp, env);
		if (ctmp == NULL)
		{
			free(tmp);
			free(command);
			return (return_perror(-1, "error ", ENOMEM));
		}
		ret = cut_instruction_dependency(inst, ctmp, &i, command);
		if (ret == -1 || ret == 0)
			return (ret);
	}
	return (1);
}
