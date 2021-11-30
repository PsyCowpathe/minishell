/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:26:48 by agirona           #+#    #+#             */
/*   Updated: 2021/11/30 18:27:52 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(void)
{
	int		i;
	int		d;
	int		j;
	int		count;
	char	**res;

	i = 0;
	while (g_envp[i])
	{
		if (ft_strncmp(g_envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	count = 1;
	d = 5;
	while (g_envp[i][d])
	{
		if (g_envp[i][d] == ':')
			count++;
		d++;
	}
	res = malloc(sizeof(char *) * count + 1);
	if (res == NULL)
		return (NULL);
	d = 5;
	j = 0;
	while (g_envp[i][d])
	{
		count = size_to_char(g_envp[i], d, ":");
		res[j] = malloc(sizeof(char) * (count + 1));
		if (res[j] == NULL)
			return (NULL);
		cpy_instruction(res[j], g_envp[i], &d, count);
		if (g_envp[i][d])
			d++;
		j++;
	}
	res[j] = NULL;
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

void	exec_path(t_cmd *cmd)
{
	pid_t	pid;
	char	**path;
	char	*tmp;
	int		i;

	path = get_path();
	i = 0;
	while (cmd->ret[0] == -1 && path[i])
	{
		cmd->ret[0] = 0;
		pid = fork();
		if (pid == 0)
		{
			tmp = join_path(cmd->exec, path[i]);
			cmd->ret[0] = execve(tmp, cmd->args, g_envp);
			if (cmd->ret[0] == 0)
				exit(0);
		}
		while ((wait(&pid)) > 0)
			NULL;
		i++;
	}
}
