/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:03:55 by agirona           #+#    #+#             */
/*   Updated: 2022/02/26 01:37:57 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_child(t_cmd *cmd)
{
	close(cmd->fd[0]);
	create_input_redirection(cmd);
	if (create_output_redirection(cmd) != 1)
		dup2(cmd->fd[1], STDOUT_FILENO);
	close(cmd->fd[1]);
	if (cmd->builtin > 0)
		;//simple->builtin();
	else if (exec_path(cmd) == 0)
	{
		perror("Error");
		if (errno == 13 || errno == 20)
			exit(126);
		exit(127);
	}
	exit(0);
}

void	last_child(t_cmd *cmd)
{
	close(cmd->fd[0]); // !
	close(cmd->fd[1]); // !
	if (create_input_redirection(cmd) != 1)
		dup2(cmd->prev->fd[0], STDIN_FILENO);
	close(cmd->prev->fd[0]);
	create_output_redirection(cmd);
	if (cmd->builtin > 0)
		;//simple->builtin();
	else if (exec_path(cmd) == 0)
	{
		perror("Error");
		if (errno == 13 || errno == 20)
			exit(126);
		exit(127);
	}
	exit(0);
}

void	perfect_child(t_cmd *cmd)
{
	if (create_input_redirection(cmd) != 1)
		dup2(cmd->prev->fd[0], STDIN_FILENO);
	close(cmd->prev->fd[0]);
	if (create_output_redirection(cmd) != 1)
		dup2(cmd->fd[1], STDOUT_FILENO);
	close(cmd->fd[1]);
	if (cmd->builtin > 0)
		;//simple->builtin();
	else if (exec_path(cmd) == 0)
	{
		perror("Error");
		if (errno == 13 || errno == 20)
			exit(126);
		exit(127);
	}
	exit(0);
}
