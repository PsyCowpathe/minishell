/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:46:13 by agirona           #+#    #+#             */
/*   Updated: 2021/12/17 16:56:16 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:25:49 by agirona           #+#    #+#             */
/*   Updated: 2021/12/17 16:44:19 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		ft_putstr(cmd->args[i]);
		if (cmd->args[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (cmd->echo_flag != 1)
		ft_putchar('\n');
}

void	exec_unset(t_cmd *cmd)
{
	t_env	*current;
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		current = cmd->env;
		while (current)
		{
			if (ft_strcmp(cmd->args[i], current->key) == 0)
				current->set = 0;
			current = current->next;
		}
		i++;
	}
}

void	exec_env(t_cmd *cmd)
{
	t_env	*current;

	current = cmd->env;
	while (current)
	{
		if (current->set == 1)
		{
			ft_putstr(current->str);
			ft_putchar('\n');
		}
		current = current->next;
	}
}

void	exec_export(t_cmd *cmd)
{
	t_env	*current;

	current = cmd->env;
	while (current)
	{
		if (current->set == 1)
		{
			ft_putstr(current->str);
			ft_putchar('\n');
		}
		current = current->next;
	}
}

void	exec_pwd(t_cmd *cmd)
{
	t_env	*current;

	current = cmd->env;
	while (current && ft_strcmp("PWD", current->key) != 0)
		current = current->next;
	ft_putstr(current->value);
	ft_putchar('\n');
}

void	exec_exit(t_cmd *cmd)
{
	if (cmd->args[1])
		exit(ft_atoi(cmd->args[1]));
	else
		exit(0);
}

void	exec_cd(t_cmd *cmd)
{
	//oulaaah
}

void	simple_builtin(t_cmd *cmd)
{
	if (cmd->builtin == 1)
		exec_cd(cmd);
	else if (cmd->builtin == 2)
		exec_echo(cmd);
	else if (cmd->builtin == 3)
		exec_pwd(cmd);
	else if (cmd->builtin == 5)
		exec_unset(cmd);
	else if (cmd->builtin == 6)
		exec_env(cmd);
}
