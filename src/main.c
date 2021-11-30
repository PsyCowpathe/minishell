/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:25 by agirona           #+#    #+#             */
/*   Updated: 2021/11/30 16:58:29 by agirona          ###   ########lyon.fr   */
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

void	exec_instruction(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		cmd->ret[0] = execve(cmd->exec, cmd->args, g_envp);
		if (cmd->ret[0] == 0)
			exit(0);
	}
	while ((wait(&pid)) > 0)
		NULL;
	if (cmd->ret[0] == -1)
		exec_path(cmd);
}

void	exec_line(t_inst *inst, char *input, int *i)
{
	int		size;
	char	*instruction;

	while (input[*i])
	{
		while (ft_iswhitespace(input[*i]) == 1)
			*i = *i + 1;
		size = size_to_char(input, *i, ";");
		if (size == -1)
			return ;
		if (new_malloc((void **)&instruction, sizeof(char), size + 1) == 0)
			return ;
		cpy_instruction(instruction, input, i, size);
		inst = instnew(ft_strdup(instruction));
		free(instruction);
		if (input[*i] == ';')
			*i = *i + 1;
		cut_instruction(inst);
		if (inst->cmds->builtin == 0)
			exec_instruction(inst->cmds);
		//print_debug(inst);
		instclear(inst);
	}
}

int	main(int argc, char **argv, char *const envp[])
{
	int		exec_ret;
	char	*input;
	int		i;
	t_inst	inst;
	(void)argc;
	(void)argv;

	g_envp = envp;
	exec_ret = 0;
	while (exec_ret == 0)
	{
		i = 0;
		input = readline("minishell$> ");
		add_history(input);
		exec_line(&inst, input, &i);
	}
	//rl_clear_history();
	return (0);
}
