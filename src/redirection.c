/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:06:46 by agirona           #+#    #+#             */
/*   Updated: 2022/02/22 15:15:18 by agoublai         ###   ########lyon.fr   */
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
		if (cmd->str[i] != c && !(c == '<' && cmd->str[i] == '>'))
		{
			ft_putstr("Error: redirection\n");
			return (-1);
		}
		if (i >= save + 2)
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

int	odd_behaviour(t_cmd *cmd, int *i)
{
	char	*file;
	int		fd;

	*i = *i + 2;
	if (!cmd->str[*i] || ft_iswhitespace(cmd->str[*i]) != 1)
		return (-1); //error
	while (ft_iswhitespace(cmd->str[*i]) == 1)
			(*i)++;
	if (cpy_size_to_char(&file, cmd->str, i, " \r\n\v\t\f") != 1)
		return (-2); //error
	file = dollar_expand(file, cmd->env, 0, 0); //error
	fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (-3); //error
	close(fd);
	return (0);
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
		else if (cmd->str[(*i) + 1] == '>')
			*ret = odd_behaviour(cmd, i);
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
	free(fragment);
	return (ret);
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
		if (ret != 1)
			return (free_fragment(fragment, ret));
		ret = verif_open(cmd, fragment, redir_type);
		if (ret != 1)
			return (free_fragment(fragment, ret));
		if (fragment)
			free(fragment);
		return (1);
	}
	if (redir_type < 0)
		{;}//error
	return (0);
}
