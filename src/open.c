/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:36:27 by agirona           #+#    #+#             */
/*   Updated: 2022/02/27 04:37:54 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_open_heredoc(void)
{
	int		fd;

	fd = open(".heredoc.tmp", O_WRONLY, 0644);
	if (fd != -1)
	{
		close(fd);
		return (unlink(".heredoc.tmp"));
	}
	return (1);
}

int	verif_open_in(t_cmd *cmd, char *fragment, int redir_type)
{
	int		fd;

	fd = -1;
	if (cmd->redir_in)
		free(cmd->redir_in);
	cmd->redir_in = ft_strdup(fragment);
	free(fragment);
	if (cmd->redir_in == NULL)
		return (-40);
	if (redir_type == 2)
	{
		fd = open(cmd->redir_in, O_RDONLY, 0644);
		if (fd == -1)
			return (return_perror(-2, "error ", errno));
		close(fd);
	}
	else if (verif_open_heredoc() < 0)
		return (return_error(-3));
	return (1);
}

int	verif_open_out(t_cmd *cmd, char *fragment, int redir_type)
{
	int		fd;

	fd = -1;
	if (cmd->redir_out)
		free(cmd->redir_out);
	cmd->redir_out = ft_strdup(fragment);
	free(fragment);
	if (cmd->redir_out == NULL)
		return (-40);
	if (redir_type == 3)
	{
		fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (return_perror(-2, "error ", errno));
	}
	else
	{
		fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (return_perror(-2, "error ", errno));
	}
	close(fd);
	return (1);
}

int	verif_open(t_cmd *cmd, char *fragment, int redir_type)
{
	int		ret;

	fragment = dollar_expand(fragment, cmd->env, 0, 0);
	if (fragment == (char *)1)
		return (-1);
	if ((redir_type - 1) / 2 == 0)
	{
		ret = verif_open_in(cmd, fragment, redir_type);
		if (ret == -1)
			return (-5);
		if (ret == -40)
			return (-1);
	}
	else
	{
		ret = verif_open_out(cmd, fragment, redir_type);
		if (ret == -40)
			return (-1);
		if (ret != 1)
			return (ret);
	}
	return (1);
}
