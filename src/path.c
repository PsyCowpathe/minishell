/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:26:48 by agirona           #+#    #+#             */
/*   Updated: 2022/02/26 01:31:30 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**get_path(t_env *env, int i, int d)
{
	char	**res;
	int		count;

	while (env && ft_strcmp(env->key, "PATH") != 0)
		env = env->next;
	count = path_count(env->str);
	if (new_malloc((void *)&res, sizeof(char *), count + 1) == 0)
		return (NULL); //error
	if (env->set == 0)
	{
		res[0] = NULL;
		return (res);
	}
	if (res == NULL)
		return (NULL);
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

void	exec_lonely_path(t_cmd *cmd, char **env_tab)
{
	char	**path;
	char	*tmp;
	int		i;

	path = get_path(cmd->env, 0, 0); //error
	i = 0;
	while (cmd->ret[0] == -1 && path[i])
	{
		cmd->ret[0] = 0;
		tmp = join_path(cmd->exec, path[i]);
		cmd->ret[0] = execve(tmp, cmd->args, env_tab);
		free(tmp);
	/*	if (cmd->ret[0] == 0)
		{
			envtab_clear(path);
			envtab_clear(env_tab);
			exit(127);
		}*/
		i++;
	}
	if (cmd->ret[0] == -1)
		perror(NULL);
	envtab_clear(path);
	envtab_clear(env_tab);
	exit(127);
}

int	test_all_path(t_cmd *cmd, char	**env_tab)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	path = get_path(cmd->env, 0, 0);
	while (cmd->ret[0] == -1 && path[i])
	{
		cmd->ret[0] = 0;
		tmp = join_path(cmd->exec, path[i]);
		cmd->ret[0] = execve(tmp, cmd->args, env_tab);
		free(tmp);
		i++;
	}
	envtab_clear(path);
	envtab_clear(env_tab);
	return (0);
}

int	exec_path(t_cmd *cmd)
{
	char	**env_tab;

	env_tab = build_env_tab(cmd);
	cmd->ret[0] = execve(cmd->exec, cmd->args, env_tab);
	return (test_all_path(cmd, env_tab));
}
