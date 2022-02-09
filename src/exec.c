/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:23:48 by agirona           #+#    #+#             */
/*   Updated: 2022/02/08 16:38:21 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_lonely(t_cmd *cmd)
{
	pid_t	cpid;

	if (cmd->is_valid != 1)
		return ;
	cpid = fork();
	if (cpid == 0)
	{
		create_input_redirection(cmd);
		create_output_redirection(cmd);
		cmd->ret[0] = execve(cmd->exec, cmd->args, build_env_tab(cmd));
		if (cmd->ret[0] == -1)
			exec_lonely_path(cmd);
		exit(0);
	}
	while (wait(&cpid) > 0)
		;
}

int	exec_first(t_cmd *cmd)
{
	pid_t	cpid;

	pipe(cmd->fd);
	cpid = fork();
	if (cpid == -1)
	{
		ft_putstr("Error: Fork creation  failed !\n");
		return (0);
	}
	if (cpid == 0)
		first_child(cmd);
	else
	{
		close(cmd->fd[1]);
		while (wait(&cpid) > 0)
			;
	}
	return (1);
}

int	exec_mid(t_cmd *cmd)
{
	pid_t	cpid;

	pipe(cmd->fd);
	cpid = fork();
	if (cpid == -1)
	{
		ft_putstr("Error: Fork creation  failed !\n");
		return (0);
	}
	if (cpid == 0)
		perfect_child(cmd);
	else
	{
		close(cmd->fd[1]);
		close(cmd->prev->fd[0]);
		while (wait(&cpid) > 0)
			;
	}
	return (1);
}

int	exec_last(t_cmd *cmd)
{
	pid_t	cpid;

	pipe(cmd->fd); //on peut le virer (!)
	cpid = fork();
	if (cpid == -1)
	{
		ft_putstr("Error: Fork creation  failed !\n");
		return (0);
	}
	if (cpid == 0)
		last_child(cmd); //!
	else
	{
		close(cmd->fd[0]); // !
		close(cmd->fd[1]);// !
		while (wait(&cpid) > 0)
			;
		close(cmd->prev->fd[0]);
	}
	return (1);
}

void	exec_pipe(t_cmd	*cmd)
{
	if (cmd->is_valid == 1)
	{
		exec_first(cmd);
	}
	cmd = cmd->next;
	while (cmd->next)
	{
		if (cmd->is_valid == 1)
			exec_mid(cmd);
		cmd = cmd->next;
	}
	if (cmd->is_valid == 1)
		exec_last(cmd);
}
