/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:11:08 by agirona           #+#    #+#             */
/*   Updated: 2021/12/16 16:15:27 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_input_redirection(t_cmd *cmd)
{
	int		fd;

	if (cmd->redir_type[1] == 2)
	{
		fd = open(cmd->redir_in, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (1);
	}
	return (0);
}

int	create_output_redirection(t_cmd *cmd)
{
	int		fd;

	if (cmd->redir_type[0] == 3)
	{
		fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (1);
	}
	else if (cmd->redir_type[0] == 4)
	{
		fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (1);
	}
	return (0);
}
