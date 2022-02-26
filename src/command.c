/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:35:29 by agirona           #+#    #+#             */
/*   Updated: 2022/02/26 03:07:15 by agirona          ###   ########lyon.fr   */
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

void	cut_exec(t_cmd *cmd, int *i)
{
	char	*fragment;
	int		size;

	while (ft_iswhitespace(cmd->str[*i]))
		(*i)++;
	size = size_to_char(cmd->str, *i, " \r\n\v\t\f");
	if (size == -1)
		return ;
	fragment = malloc(sizeof(char) * (size + 1));
	if (fragment == NULL)
		return ;
	cpy_instruction(fragment, cmd->str, i, size);
	cmd->exec = ft_strdup(fragment);
	free(fragment);
}

int	cut_args(t_cmd *cmd, int j, int *i, int ret)
{
	int		size;
	char	*tmp;

	while (cmd->str[*i] && ret == 1)
	{
		ret = cut_redir(cmd, i);
		if (ret < 0)
			return (-1);
	}
	while (ft_iswhitespace(cmd->str[*i]) == 1)
		*i = *i + 1;
	size = size_to_char(cmd->str, *i, " \r\n\v\t\f");
	if (size == -1)
		return (-1);
	if (size == 0)
	{
		cmd->args[j] = NULL;
		return (1);
	}
	if (new_malloc((void **)&tmp, sizeof(char), size + 1) == 0)
		return (-1);
	cpy_instruction(tmp, cmd->str, i, size);
	cmd->args[j] = ft_strdup(tmp);
	free(tmp);
	return (1);
}

int	get_args(t_cmd *cmd, int i)
{
	int		j;

	j = 1;
	cmd->args = malloc(sizeof(char *) * (count_args(cmd->str, i) + 2));
	if (cmd->args == NULL)
		return (-1);
	cmd->args[0] = malloc(sizeof(char) * 1);
	if (cmd->args[0] == NULL)
		return (-1);
	cmd->args[0][0] = '\0';
	cmd->args[1] = NULL;
	while (ft_iswhitespace(cmd->str[i]) == 1)
		i++;
	while (cmd->str[i])
	{
		if (cut_args(cmd, j, &i, 1) != 1)
			return (-1);
		j++;
	}
	cmd->args[j] = NULL;
	return (1);
}

int	cut_command(t_cmd *cmd)
{
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	while (ft_iswhitespace(cmd->str[i]) == 1)
		i++;
	while (cmd->str[i] && ret == 1)
	{
		ret = cut_redir(cmd, &i);
		if (ret < 0)
			return (0);
	}
	cut_exec(cmd, &i);
	if (strcmp_quote(cmd->exec, "echo") == 1) // on le decale dans le is_builtin
		i = get_echo_flag(cmd, cmd->str, i);
	cmd->builtin = is_builtin(cmd);
	if (get_args(cmd, i) <= 0)
		return (0);
	cmd->exec = dollar_expand(cmd->exec, cmd->env, 0, 0);
	free(cmd->args[0]);
	cmd->args[0] = cmd->exec;
	expand_args(cmd);
	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
		cmd->is_path = 1;
	cmd->is_valid = 1;
	return (1);
}
