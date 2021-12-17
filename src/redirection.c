/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:06:46 by agirona           #+#    #+#             */
/*   Updated: 2021/12/17 18:22:08 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection(t_cmd *cmd, int i)
{
	int		save;
	char	c;
	int		trigger;

	c = '\0';
	save = i;
	trigger = 0;
	while (ft_ischar("><", cmd->str[i]) == 1)
	{
		trigger = 1;
		if (i == save)
			c = cmd->str[i];
		if (cmd->str[i] != c)
		{
			ft_putstr("Error: redirection\n");
			return (-1);
		}
		if (i >= save + 3)
		{
			ft_putstr("Error: redirection\n");
			return (-2);
		}
		i++;
	}
	while (ft_iswhitespace(cmd->str[i]) == 1)
		i++;
	if (trigger == 1 && !cmd->str[i])
	{
		ft_putstr("Error: redirection\n");
		return (-3);
	}
	if (ft_ischar("><", cmd->str[i]) == 1)
	{
		ft_putstr("Error: redirection\n");
		return (-4);
	}
	return (1);
}

int	is_redir(t_cmd *cmd, int i, int	*ret)
{
	*ret = check_redirection(cmd, i);
	if (*ret != 1)
		return (*ret);
	*ret = 0;
	if (cmd->str[i] == '<')
	{
		if (cmd->str[i + 1] == '<')
			*ret = 1;
		else
			*ret = 2;
	}
	else if (cmd->str[i] == '>')
	{
		if (cmd->str[i + 1] == '>')
			*ret = 3;
		else
			*ret = 4;
	}
	return (*ret);
}

int	cut_redir(t_cmd *cmd, int *i)
{
	int		redir_type;
	char	*fragment;
	int		ret;

	while (ft_iswhitespace(cmd->str[*i]) == 1)
		(*i)++;
	if (is_redir(cmd, *i, &redir_type) > 0)
	{	
		(*i) += (1 + redir_type % 2);
		while (ft_iswhitespace(cmd->str[*i]) == 1)
			(*i)++;
		if ((redir_type - 1) / 2 == 0)
			cmd->redir_type[1] = redir_type;
		else
			cmd->redir_type[0] = redir_type;
		ret = cpy_size_to_char(&fragment, cmd->str, i, " \r\n\v\t\f");
		if (ret != 1)
			return (ret);
		ret = verif_open(cmd, fragment, redir_type);
		if (ret != 1)
			return (ret);
		free(fragment);
		return (1);
	}
	return (0);
}
