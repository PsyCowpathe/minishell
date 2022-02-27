/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:23:48 by agirona           #+#    #+#             */
/*   Updated: 2022/02/27 04:37:44 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_lonely(t_cmd *cmd)
{
	pid_t	cpid;
	char	**env_tab;

	cpid = fork();
	if (cpid == -1)
		return (return_perror(-1, "error ", errno));
	if (cpid == 0)
	{
		env_tab = exec_lonely_dependency(cmd);
		cmd->ret[0] = execve(cmd->exec, cmd->args, env_tab);
		if (cmd->ret[0] == -1 && cmd->is_path == 0 && cmd->exec[0])
			exec_lonely_path(cmd, env_tab);
		perror("error ");
		envtab_clear(env_tab);
		if (errno == 13 || errno == 20)
			exit(126);
		exit(127);
	}
	set_pid(cpid);
	while (wait(&cpid) > 0)
		;
	g_pid_t[1024] = WEXITSTATUS(cpid);
	return (1);
}

int	exec_first(t_cmd *cmd)
{
	pid_t	cpid;

	if (pipe(cmd->fd) == -1)
		return (return_perror(-1, "error ", errno));
	cpid = fork();
	if (cpid == -1)
		return (return_perror(-1, "error ", errno));
	if (cpid == 0)
	{
		if (first_child(cmd) == -1)
			return (-1);
	}
	else
	{
		set_pid(cpid);
		if (close(cmd->fd[1]) == -1)
			return (return_perror(-1, "error ", errno));
	}
	return (1);
}

int	exec_mid(t_cmd *cmd)
{
	pid_t	cpid;

	if (pipe(cmd->fd) == -1)
		return (return_perror(-1, "error ", errno));
	cpid = fork();
	if (cpid == -1)
		return (return_perror(-1, "error ", errno));
	if (cpid == 0)
	{
		if (perfect_child(cmd) == -1)
			return (-1);
	}
	else
	{
		set_pid(cpid);
		if (close(cmd->fd[1]) == -1)
			return (return_perror(-1, "error ", errno));
		if (close(cmd->prev->fd[0]) == -1)
			return (return_perror(-1, "error ", errno));
	}
	return (1);
}

int	exec_last(t_cmd *cmd)
{
	pid_t	cpid;

	if (pipe(cmd->fd) == -1)
		return (return_perror(-1, "error ", errno));
	cpid = fork();
	if (cpid == -1)
		return (return_perror(-1, "error ", errno));
	if (cpid == 0)
	{
		if (last_child(cmd) == -1)
			return (-1);
	}
	else
		if (exec_last_dependency(cmd, cpid) == -1)
			return (-1);
	return (1);
}

int	exec_pipe(t_cmd	*cmd)
{
	if (exec_first(cmd) == -1)
		return (-1);
	cmd = cmd->next;
	while (cmd->next)
	{
		if (exec_mid(cmd) == -1)
			return (-1);
		cmd = cmd->next;
	}
	if (exec_last(cmd) == -1)
		return (-1);
	return (1);
}
