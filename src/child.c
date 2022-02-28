/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:03:55 by agirona           #+#    #+#             */
/*   Updated: 2022/02/28 03:09:07 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_cmd *cmd)
{
	if (cmd->builtin > 0)
	{
		if (simple_builtin(cmd) < 0)
			exit(1);
	}
	else if (exec_path(cmd) == 0)
	{
		perror("Error");
		if (errno == 13 || errno == 20)
			exit(126);
		exit(127);
	}
	exit(0);
}

int	first_child(t_cmd *cmd)
{
	int		ret;

	if (close(cmd->fd[0]) == -1)
		return (-1);
	if (create_input_redirection(cmd) == -1)
		exit(1);
	ret = create_output_redirection(cmd);
	if (ret == -1)
		exit(1);
	if (ret != 1)
		if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
			exit(return_perror(1, "error ", errno));
	if (close(cmd->fd[1]) == -1)
		exit(return_perror(1, "error ", errno));
	exec_child(cmd);
	return (105);
}

int	last_child(t_cmd *cmd)
{
	int		ret;

	if (close(cmd->fd[0]) == -1)
		return (-1);
	if (close(cmd->fd[1]) == -1)
		return (-1);
	ret = create_input_redirection(cmd);
	if (ret == -1)
		exit(1);
	if (ret != 1)
		if (dup2(cmd->prev->fd[0], STDIN_FILENO) == -1)
			exit(return_perror(1, "error ", errno));
	if (close(cmd->prev->fd[0]) == -1)
		exit(return_perror(1, "error ", errno));
	if (create_output_redirection(cmd) == -1)
		exit(1);
	exec_child(cmd);
	return (105);
}

int	perfect_child(t_cmd *cmd)
{
	int		ret;

	ret = create_input_redirection(cmd);
	if (ret == -1)
		exit(1);
	if (ret != 1)
		if (dup2(cmd->prev->fd[0], STDIN_FILENO) == -1)
			exit(return_perror(1, "error ", errno));
	if (close(cmd->prev->fd[0]) == -1)
		exit(return_perror(1, "error ", errno));
	ret = create_output_redirection(cmd);
	if (ret == -1)
		exit(1);
	if (ret != 1)
		if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
			exit(return_perror(1, "error ", errno));
	if (close(cmd->fd[1]) == -1)
		exit(return_perror(1, "error ", errno));
	exec_child(cmd);
	return (105);
}
