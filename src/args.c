/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 03:31:12 by agirona           #+#    #+#             */
/*   Updated: 2022/02/28 03:07:03 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_dependency(t_cmd *cmd, int *i, int *size, int j)
{
	while (ft_iswhitespace(cmd->str[*i]) == 1)
		*i = *i + 1;
	*size = size_to_char(cmd->str, *i, " \r\n\v\t\f");
	if (*size == -1)
		return (0);
	if (*size == 0)
	{
		cmd->args[j] = NULL;
		return (1);
	}
	return (105);
}

int	cut_args(t_cmd *cmd, int j, int *i, int ret)
{
	int		size;
	char	*tmp;

	while (cmd->str[*i] && ret == 1)
	{
		ret = cut_redir(cmd, i);
		if (ret == -3)
			return (-3);
		if (ret == -2)
			return (return_perror(-1, "error ", ENOMEM));
		if (ret < 0)
			return (0);
	}
	ret = args_dependency(cmd, i, &size, j);
	if (ret == 0 || ret == 1)
		return (ret);
	if (new_malloc((void **)&tmp, sizeof(char), size + 1) == 0)
		return (return_perror(-1, "error ", ENOMEM));
	cpy_instruction(tmp, cmd->str, i, size);
	cmd->args[j] = ft_strdup(tmp);
	free(tmp);
	if (cmd->args[j] == NULL)
		return (return_perror(-1, "error ", ENOMEM));
	return (1);
}

int	get_args(t_cmd *cmd, int i)
{
	int		j;
	int		ret;

	j = 1;
	cmd->args = malloc(sizeof(char *) * (count_args(cmd->str, i) + 2));
	if (cmd->args == NULL)
		return (-2);
	cmd->args[0] = malloc(sizeof(char) * 1);
	if (cmd->args[0] == NULL)
		return (-2);
	cmd->args[0][0] = '\0';
	cmd->args[1] = NULL;
	while (ft_iswhitespace(cmd->str[i]) == 1)
		i++;
	while (cmd->str[i])
	{
		ret = cut_args(cmd, j, &i, 1);
		if (ret == 0)
			return (0);
		if (ret != 1)
			return (-1);
		j++;
	}
	cmd->args[j] = NULL;
	return (1);
}
