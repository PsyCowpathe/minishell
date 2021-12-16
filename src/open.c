/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:36:27 by agirona           #+#    #+#             */
/*   Updated: 2021/12/16 20:29:30 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	verif_open_heredoc(void)
{
	int		fd;

	fd = open(".heredoc.tmp", O_WRONLY, 0644);
	if (fd != -1)
	{
		close(fd);
		unlink(".heredoc.tmp");
	}
}

int	verif_open_in(t_cmd *cmd, char *fragment, int redir_type)
{
	int		fd;

	fd = -1;
	if (cmd->redir_in)
		free(cmd->redir_in);
	cmd->redir_in = ft_strdup(fragment);
	if (redir_type == 2)
	{
		fd = open(cmd->redir_in, O_RDONLY, 0644);
		if (fd == -1)
		{
			ft_putstr("Error: j'ai pas les droit de lecture ou alors");
			ft_putstr(" il existe pas ton fichier frero\n");
			return (-1);
		}
		close(fd);
	}
	else
		verif_open_heredoc();
	return (1);
}

int	verif_open_out(t_cmd *cmd, char *fragment, int redir_type)
{
	int		fd;

	fd = -1;
	if (cmd->redir_out)
		free(cmd->redir_out);
	cmd->redir_out = ft_strdup(fragment);
	if (redir_type == 3)
	{
		fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_putstr("Error: J'ai po reussi a creer :(\n");
			return (-3);
		}
	}
	else
	{
		fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr("Error: J'ai pas reussi a creer\n");
			return (-18);
		}
	}
	close(fd);
	return (1);
}

int	verif_open(t_cmd *cmd, char *fragment, int redir_type)
{
	int		ret;

	if ((redir_type - 1) / 2 == 0)
	{
		if (verif_open_in(cmd, fragment, redir_type) == -1)
			return (-5);
	}
	else
	{
		ret = verif_open_out(cmd, fragment, redir_type);
		if (ret != 1)
			return (ret);
	}
	return (1);
}
