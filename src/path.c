/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:26:48 by agirona           #+#    #+#             */
/*   Updated: 2022/02/16 15:35:04 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		path_count(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == ':')
			count++;
		i++;
	}
	return (count);
}

char	**get_path(t_env *env)
{
	char	**res;
	int		count;
	int		i;
	int		d;

	while (env && ft_strcmp(env->key, "PATH") != 0)
		env = env->next;
	count = path_count(env->str);
	res = malloc(sizeof(char *) * (count + 1));
	if (env->set == 0)
	{
		res[0] = NULL;
		return (res);
	}
	if (res == NULL)
		return (NULL);
	d = 0;
	i = 0;
	while (env->str[i])
	{
		cpy_size_to_char(&res[d], env->str, &i, ":");
		if (env->str[i])
			i++;
		d++;
	}
	res[d] = NULL;
	return (res);
}

char	*join_path(char *exec, char *path)
{
	char	*new_exec;
	char	*ret;
	char	*tmp;

	new_exec = ft_strtrim(exec, "\"\'");
	tmp = ft_strjoin("/", new_exec);
	ret = ft_strjoin(path, tmp);
	free(new_exec);
	free(tmp);
	return (ret);
}

void	exec_lonely_path(t_cmd *cmd)
{
	pid_t	pid;
	char	**path;
	char	*tmp;
	int		i;

	path = get_path(cmd->env); //error
	i = 0;
	while (cmd->ret[0] == -1 && path[i])
	{
		cmd->ret[0] = 0;
		pid = fork();
		if (pid == 0)
		{
			tmp = join_path(cmd->exec, path[i]);
			cmd->ret[0] = execve(tmp, cmd->args, build_env_tab(cmd));
			if (cmd->ret[0] == 0)
				exit(0);
		}
		while ((wait(&pid)) > 0)
			;
		i++;
	}
	if (cmd->ret[0] == -1)
		ft_putstr("Error: command not found\n");
}

int		exec_path(t_cmd *cmd)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	cmd->ret[0] = execve(cmd->exec, cmd->args, build_env_tab(cmd));
	if (cmd->ret[0] == 0)
		exit(0);
	else
	{
		path = get_path(cmd->env);
		while (cmd->ret[0] == -1 && path[i])
		{
			cmd->ret[0] = 0;
			tmp = join_path(cmd->exec, path[i]);
			cmd->ret[0] = execve(tmp, cmd->args, build_env_tab(cmd));
			if (cmd->ret[0] == 0)
				exit(0);
			i++;
		}
		return (0);
	}
	return (1);
}
