/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:25:49 by agirona           #+#    #+#             */
/*   Updated: 2022/02/22 15:39:58 by agoublai         ###   ########lyon.fr   */
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

/*int		relative(t_cmd *cmd, char *pwd)
{
	int		i;
	int		d;

	i = 0;
	d = 0;
	while (pwd[d])
		d++;
	while (cmd->args[1][i])
	{
		if (cmd->args[1][i] == '.' && cmd->args[1][i + 1] == '/')
			i = i + 2;
		else if (cmd->args[1][i + 2] && cmd->args[1][i] == '.'
			&& cmd->args[1][i + 1] == '.' && cmd->args[1][i + 2] == '/')
		{
			d = 0;
			while (pwd[d] && pwd[d] != '/')
				d--;
		}
	}
}

void	exec_cd(t_cmd *cmd)
{
	struct stat path_stat;
	t_env	*current;
	char	*tmp;

    stat(cmd->args[1], &path_stat);
    if (S_ISDIR(path_stat.st_mode) == 1)
	{
		while (current && ft_strcmp(current->key, "PWD") == 0)
			current = current->next;
		tmp = ft_strdup(current->value);
		if (cmd->args[1][0] == '.')
			relative(cmd, tmp);
	}
	else
		ft_putstr("Error: No such file or directory\n");
}*/

void	simple_builtin(t_cmd *cmd)
{
	if (cmd->builtin == 1)
		;//exec_cd(cmd);
	else if (cmd->builtin == 2)
		exec_echo(cmd);
	else if (cmd->builtin == 3)
		exec_pwd(cmd);
	else if (cmd->builtin == 5)
		exec_unset(cmd);
	else if (cmd->builtin == 6)
		exec_env(cmd);
}
