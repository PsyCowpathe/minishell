/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:03:55 by agirona           #+#    #+#             */
/*   Updated: 2021/12/16 20:29:31 by agirona          ###   ########lyon.fr   */
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
		ft_putstr("Error: Incorrect command or path\n");
	exit(0);
}

void	last_child(t_cmd *cmd)
{
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	if (create_input_redirection(cmd) != 1)
		dup2(cmd->prev->fd[0], STDIN_FILENO);
	close(cmd->prev->fd[0]);
	create_output_redirection(cmd);
	if (cmd->builtin > 0)
		;//simple->builtin();
	else if (exec_path(cmd) == 0)
		ft_putstr("Error: Incorrect command or path\n");
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
		ft_putstr("Error: Incorrect command or path\n");
	exit(0);
}
