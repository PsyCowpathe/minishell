/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:06:46 by agirona           #+#    #+#             */
/*   Updated: 2022/02/27 22:02:57 by agirona          ###   ########lyon.fr   */
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
			return (return_error(-2));
		if (i >= save + 2)
			return (return_error(-2));
		i++;
	}
	while (ft_iswhitespace(cmd->str[i]) == 1)
		i++;
	if (trigger == 1 && !cmd->str[i])
		return (return_error(-2));
	if (ft_ischar("><", cmd->str[i]) == 1)
		return (return_error(-2));
	return (1);
}

int	is_redir(t_cmd *cmd, int *i, int *ret)
{
	*ret = check_redirection(cmd, *i);
	if (*ret != 1)
		return (*ret);
	*ret = 0;
	if (cmd->str[*i] == '<')
	{
		if (cmd->str[(*i) + 1] == '<')
			*ret = 1;
		else
			*ret = 2;
	}
	else if (cmd->str[*i] == '>')
	{
		if (cmd->str[(*i) + 1] == '>')
			*ret = 3;
		else
			*ret = 4;
	}
	return (*ret);
}

int	free_fragment(char *fragment, int ret)
{
	if (fragment)
		free(fragment);
	return (ret);
}

int	cut_redir_dependency(t_cmd *cmd, char *fragment, int ret, int redir_type)
{
	if (ret == -1)
		return (-2);
	ret = verif_open(cmd, fragment, redir_type);
	if (ret == -3)
		return (-3);
	if (ret == -1)
		return (free_fragment(fragment, -2));
	if (ret != 1)
		return (free_fragment(fragment, -1));
	if (fragment)
		free(fragment);
	return (1);
}

int	cut_redir(t_cmd *cmd, int *i)
{
	int		redir_type;
	char	*fragment;
	int		ret;

	while (ft_iswhitespace(cmd->str[*i]) == 1)
		(*i)++;
	if (is_redir(cmd, i, &redir_type) > 0)
	{	
		(*i) += (1 + redir_type % 2);
		while (ft_iswhitespace(cmd->str[*i]) == 1)
			(*i)++;
		if ((redir_type - 1) / 2 == 0)
			cmd->redir_type[1] = redir_type;
		else
			cmd->redir_type[0] = redir_type;
		ret = cpy_size_to_char(&fragment, cmd->str, i, " \r\n\v\t\f");
		ret = cut_redir_dependency(cmd, fragment, ret, redir_type);
		if (ret < 0)
			return (ret);
		return (1);
	}
	if (redir_type < 0)
		return (-1);
	return (0);
}
