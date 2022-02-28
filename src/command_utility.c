/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:57:58 by agirona           #+#    #+#             */
/*   Updated: 2022/02/28 03:07:07 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strcmp_quote(char *str, char *find)
{
	int		i;
	int		d;

	i = 0;
	d = 0;
	while (str[i] || find[d])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		else
		{
			if (str[i] != find[d])
				return (0);
			if (str[i])
				i++;
			if (find[d])
				d++;
		}
	}
	return (1);
}

int	is_builtin(t_cmd *cmd)
{
	if (strcmp_quote(cmd->exec, "cd") == 1)
		return (1);
	if (strcmp_quote(cmd->exec, "echo") == 1)
		return (2);
	if (strcmp_quote(cmd->exec, "pwd") == 1)
		return (3);
	if (strcmp_quote(cmd->exec, "export") == 1)
		return (4);
	if (strcmp_quote(cmd->exec, "unset") == 1)
		return (5);
	if (strcmp_quote(cmd->exec, "env") == 1)
		return (6);
	if (strcmp_quote(cmd->exec, "exit") == 1)
		return (7);
	return (0);
}

int	count_args(char	*str, int i)
{
	int		count;
	char	c;

	count = 0;
	while (ft_iswhitespace(str[i]) == 1)
			i++;
	while (str[i])
	{
		while (ft_iswhitespace(str[i]) == 1)
			i++;
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				i++;
			i++;
		}
		while (str[i] && ft_iswhitespace(str[i]) == 0)
			i++;
		count++;
	}
	return (count);
}

int	shift_args(t_cmd *cmd, int i)
{
	int		j;

	j = i;
	while (cmd->args[i] && cmd->args[i][0] == '\0')
		i++;
	while (cmd->args[i] && cmd->args[i][0] != '\0')
	{
		cmd->args[j] = ft_strdup(cmd->args[i]);
		if (cmd->args[j] == NULL)
			return (-2);
		free(cmd->args[i]);
		cmd->args[i] = ft_strdup("\0");
		if (cmd->args[i] == NULL)
			return (-2);
		i++;
		j++;
	}
	return (1);
}

int	expand_args(t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		cmd->args[i] = dollar_expand(cmd->args[i], cmd->env, 0, 0);
		if (cmd->args[i] == (char *)1)
			return (return_perror(-2, "error ", ENOMEM));
		i++;
	}
	i = 1;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '\0')
			if (shift_args(cmd, i) == -2)
				return (return_perror(-2, "error ", ENOMEM));
		i++;
	}
	return (1);
}
