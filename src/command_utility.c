/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:57:58 by agirona           #+#    #+#             */
/*   Updated: 2021/11/29 19:44:05 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strcmp_quote(char *str, char *find)
{
	int		i;
	int		trigger;
	int		d;
	char	c;

	i = 0;
	trigger = 0;
	if (str[i] == '"' || str[i] == '\'')
	{
		trigger++;
		c = str[i];
		while (str[i] == c)
			i++;
	}
	d = 0;
	while (str[i] && find[d])
	{
		if (str[i] != find[d])
			return (0);
		i++;
		d++;
		while (str[i] == c)
		{
			trigger++;
			i++;
		}
	}
	if ((trigger % 2 == 0 && ft_iswhitespace(str[i]) == 1) || str[i] == '\0')
		return (1);
	return (0);
}

int	is_builtin(t_cmd *cmd)
{
	if (strcmp_quote(cmd->exec, "cd") == 1)
		return (1);
	if (strcmp_quote(cmd->exec, "echo") == 1)
		return (1);
	if (strcmp_quote(cmd->exec, "pwd") == 1)
		return (1);
	if (strcmp_quote(cmd->exec, "export") == 1)
		return (1);
	if (strcmp_quote(cmd->exec, "unset") == 1)
		return (1);
	if (strcmp_quote(cmd->exec, "env") == 1)
		return (1);
	if (strcmp_quote(cmd->exec, "exit") == 1)
		return (1);
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
