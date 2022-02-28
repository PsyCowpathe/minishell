/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:35:29 by agirona           #+#    #+#             */
/*   Updated: 2022/02/27 22:02:55 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_echo_flag(t_cmd *cmd, char *str, int i)
{
	int		save;
	char	quote;

	quote = 0;
	while (str[i] && ft_iswhitespace(str[i]) == 1)
		i = i + 1;
	save = i;
	if (str[i] == '"' || str[i] == '\'')
	{
		quote = str[i];
		i++;
	}
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		if ((quote && str[i + 2] == quote) || (quote == 0 && (str[i + 2] == '\0'
					|| ft_iswhitespace(str[i + 2]) == 1)))
		{
			cmd->echo_flag = 1;
			if (quote)
				i++;
			return (i + 2);
		}
	}
	return (save);
}

int	cut_exec(t_cmd *cmd, int *i)
{
	char	*fragment;
	int		size;

	while (ft_iswhitespace(cmd->str[*i]))
		(*i)++;
	size = size_to_char(cmd->str, *i, " \r\n\v\t\f");
	if (size == -1)
		return (-1);
	fragment = malloc(sizeof(char) * (size + 1));
	if (fragment == NULL)
		return (-2);
	cpy_instruction(fragment, cmd->str, i, size);
	cmd->exec = ft_strdup(fragment);
	free(fragment);
	if (cmd->exec == NULL)
		return (-2);
	return (0);
}

int	command_dependency(t_cmd *cmd, int i)
{
	int		ret;

	ret = get_args(cmd, i);
	if (ret == -1)
		return (-1);
	if (ret <= 0)
		return (0);
	cmd->exec = dollar_expand(cmd->exec, cmd->env, 0, 0);
	if (cmd->exec == (char *)1)
		return (return_perror(-1, "error ", ENOMEM));
	if (cmd->exec == NULL)
		return (0);
	cmd->builtin = is_builtin(cmd);
	free(cmd->args[0]);
	cmd->args[0] = cmd->exec;
	if (expand_args(cmd) == -2)
		return (-1);
	if (cmd->args [0] && (cmd->args[0][0] == '/' || cmd->args[0][0] == '.'))
		cmd->is_path = 1;
	return (1);
}

int	cut_command(t_cmd *cmd, int i, int ret)
{
	while (ft_iswhitespace(cmd->str[i]) == 1)
		i++;
	while (cmd->str[i] && ret == 1)
	{
		ret = cut_redir(cmd, &i);
		if (ret == -2)
			return (return_perror(-1, "error ", ENOMEM));
		if (ret == -3)
			return (-1);
		if (ret < 0)
			return (0);
	}
	ret = cut_exec(cmd, &i);
	if (ret == -2)
		return (return_perror(-1, "error ", ENOMEM));
	if (ret < 0)
		return (0);
	ret = command_dependency(cmd, i);
	if (ret == -1 || ret == 0)
		return (ret);
	return (1);
}
