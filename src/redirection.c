/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:06:46 by agirona           #+#    #+#             */
/*   Updated: 2021/12/15 13:30:09 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_redir(t_cmd *cmd, int i)
{
	int		ret;
	int		save;
	char	c;

	ret = 0;
	save = i;
	c = '\0';
	while (ft_ischar("><", cmd->str[i]) == 1)
	{
		if (i == save)
			c = cmd->str[i];
		if (cmd->str[i] != c)
		{
			ft_putstr("Error: redirection");
			return (-1);
		}
		if (i >= save + 3)
		{
			ft_putstr("Error: redirection");
			return (-2);
		}
		i++;
	}
	while (ft_iswhitespace(cmd->str[i]) == 1)
		i++;
	if (ft_ischar("><", cmd->str[i]) == 1)
	{
			ft_putstr("Error: redirection");
			return (-3);
	}
	i = save;
	if (cmd->str[i] == '<')
	{
		if (cmd->str[i + 1] == '<')
			ret = 1;
		else
			ret = 2;
	}
	else if (cmd->str[i] == '>')
	{
		if (cmd->str[i + 1] == '>')
			ret = 3;
		else
			ret = 4;
	}
	return (ret);
}

int	cut_redir(t_cmd *cmd, int *i)
{
	int		size;
	int		redir_type;
	char	*fragment;
	int		fd;

	while (ft_iswhitespace(cmd->str[*i]) == 1)
		(*i)++;
	redir_type = is_redir(cmd, *i);
	if (redir_type > 0)
	{	
		(*i) += (1 + redir_type % 2);
		while (ft_iswhitespace(cmd->str[*i]) == 1)
			(*i)++;
		if ((redir_type - 1) / 2 == 0)
			cmd->redir_type[1] = redir_type;
		else
			cmd->redir_type[0] = redir_type;
		size = size_to_char(cmd->str, *i, " \r\n\v\t\f");
		if (size == -1)
			return (-14);
		fragment = malloc(sizeof(char) * (size + 1));
		if (fragment == NULL)
			return (-1);
		cpy_instruction(fragment, cmd->str, i, size);
		ft_putstr("frag = ");
		ft_putstr(fragment);
		ft_putstr("enter = ");
		ft_putstr(cmd->args[1]);
		ft_putchar('\n');

		if ((redir_type - 1) / 2 == 0)	
		{
			if (cmd->redir_in)
				free(cmd->redir_in);
			cmd->redir_in = ft_strdup(fragment);
			if (redir_type == 2)
			{
				fd = open(cmd->redir_in, O_RDONLY, 0644);
				if (fd != -1)
				{
					ft_putstr("Error: j'ai pas les droit de lecture ou alors il existe pas ton fichier frero");
					return (-5);
				}
				close(fd);
			}
			else
				ft_putstr("HEREDOC"); //ON LE FAIT OU PAS ?
		}
		else
		{
			if (cmd->redir_out)
				free(cmd->redir_out);
			cmd->redir_out = ft_strdup(fragment);
			if (redir_type == 3)
			{
				fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd == -1)
				{
					ft_putstr("Error: J'ai po reussi a creer :(");
					return (-3);
				}
				close(fd);
			}
			else
			{
				fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1)
				{
					ft_putstr("Error: J'ai pas reussi a creer");
					return (-18);
				}
				close(fd);
			}

		}
		free(fragment);
		ft_putstr("final = ");
		ft_putstr(cmd->args[1]);
		ft_putchar('\n');
		return (1);
	}
	return (0);
}
