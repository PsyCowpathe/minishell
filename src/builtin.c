/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:25:49 by agirona           #+#    #+#             */
/*   Updated: 2022/02/28 03:09:04 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(t_cmd *cmd)
{
	t_env	*current;
	int		fd;

	if (cmd->redir_out)
	{
		fd = open(cmd->redir_out, O_WRONLY);
		if (fd == -1)
			return (return_perror(-2, "error ", errno));
	}
	else
		fd = STDOUT_FILENO;
	current = cmd->env;
	while (current && ft_strcmp("PWD", current->key) != 0)
		current = current->next;
	ft_putstr_fd(current->value, fd);
	ft_putchar_fd('\n', fd);
	if (fd != STDOUT_FILENO)
		if (close(fd) == -1)
			return (return_perror(-2, "error ", errno));
	return (1);
}

int	exec_unset(t_cmd *cmd)
{
	t_env	*current;

	current = cmd->env;
	if (!cmd->args[1])
		return (1);
	while (current)
	{
		if (ft_strcmp(cmd->args[1], current->key) == 0)
		{
			current->set = 0;
			return (1);
		}
		current = current->next;
	}
	return (1);
}

int	exec_env(t_cmd *cmd)
{
	t_env	*current;
	int		fd;

	current = cmd->env;
	if (cmd->redir_out)
	{
		fd = open(cmd->redir_out, O_WRONLY);
		if (fd == -1)
			return (return_perror(-2, "error ", errno));
	}
	else
		fd = STDOUT_FILENO;
	while (current)
	{
		if (current->set == 1)
		{
			ft_putstr_fd(current->str, fd);
			ft_putchar_fd('\n', fd);
		}
		current = current->next;
	}
	return (1);
}

int	simple_builtin(t_cmd *cmd)
{
	int		ret;

	ret = 1;
	if (cmd->builtin == 1)
		ret = exec_cd(cmd);
	else if (cmd->builtin == 2)
		exec_echo(cmd, 0, 0, 0);
	else if (cmd->builtin == 3)
		exec_pwd(cmd);
	else if (cmd->builtin == 4)
		exec_export(cmd, 0, 0);
	else if (cmd->builtin == 5)
		exec_unset(cmd);
	else if (cmd->builtin == 6)
		exec_env(cmd);
	else if (cmd->builtin == 7)
		return (-1);
	if (ret != 1)
		return (ret);
	return (1);
}
