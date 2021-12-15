/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:25 by agirona           #+#    #+#             */
/*   Updated: 2021/12/15 13:03:13 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*const *g_envp = NULL;

void	exec_lonely_instruction(t_cmd *cmd)
{
	pid_t	cpid;
	int		fd;

	cpid = fork();
	if (cpid == 0)
	{
		if (cmd->redir_type[1] == 2)
		{
			fd = open(cmd->redir_in, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (cmd->redir_type[0] == 3)
		{
			fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (cmd->redir_type[0] == 4)
		{
			fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		cmd->ret[0] = execve(cmd->exec, cmd->args, g_envp);
		if (cmd->ret[0] == 0)
			exit(0);
	}
	while ((wait(&cpid)) > 0)
		;
	if (cmd->ret[0] == -1)
		exec_lonely_path(cmd);
}

int	exec_first(t_cmd *cmd)
{
	pid_t	cpid;
	int		fd;

	pipe(cmd->fd);
	cpid = fork();
	if (cpid == -1)
	{
		ft_putstr("Error: Fork creation  failed !\n");
		return (0);
	}
	if (cpid == 0)
	{
		close(cmd->fd[0]);
		if (cmd->redir_type[1] == 2)
		{
			fd = open(cmd->redir_in, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
		if (cmd->builtin > 0)
			;//simple->builtin();
		else if (exec_path(cmd) == 0)
		{
			ft_putstr("Error: Incorrect command or path\n");
			exit(0);
		}
		exit(0);
	}
	else
	{
		close(cmd->fd[1]);
		while (wait(&cpid) > 0)
			;
	}
	return (1);
}

int	exec_last(t_cmd *cmd)
{
	pid_t	cpid;
	int		fd;

	pipe(cmd->fd);
	cpid = fork();
	if (cpid == -1)
	{
		ft_putstr("Error: Fork creation  failed !\n");
		return (0);
	}
	if (cpid == 0)
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		if (cmd->redir_type[1] == 2)
		{
			fd = open(cmd->redir_in, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else
			dup2(cmd->prev->fd[0], STDIN_FILENO);
		close(cmd->prev->fd[0]);
		if (cmd->builtin > 0)
			;//simple->builtin();
		else if (exec_path(cmd) == 0)
		{
			ft_putstr("Error: Incorrect command or path\n");
			exit(0);
		}
		exit(0);
	}
	else
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		while (wait(&cpid) > 0)
			;
		close(cmd->prev->fd[0]);
	}
	return (1);
}

int	exec_mid(t_cmd *cmd)
{
	pid_t	cpid;
	int		fd;

	pipe(cmd->fd);
	cpid = fork();
	if (cpid == -1)
	{
		ft_putstr("Error: Fork creation  failed !\n");
		return (0);
	}
	if (cpid == 0)
	{
		if (cmd->redir_type[1] == 2)
		{
			fd = open(cmd->redir_in, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else
			dup2(cmd->prev->fd[0], STDIN_FILENO);
		close(cmd->prev->fd[0]);
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
		if (cmd->builtin > 0)
			;//simple->builtin();
		else if (exec_path(cmd) == 0)
		{
			ft_putstr("Error: Incorrect command or path\n");
			exit(0);
		}
		exit(0);
	}
	else
	{
		close(cmd->fd[1]);
		close(cmd->prev->fd[0]);
		while (wait(&cpid) > 0)
			;
	}
	return (1);

}

void	exec_pipe(t_cmd	*cmd)
{
	exec_first(cmd);
	cmd = cmd->next;
	while (cmd->next)
	{
		exec_mid(cmd);
		cmd = cmd->next;
	}
	exec_last(cmd);
}

void	cut_input(t_inst **inst, char *input, int *i)
{
	int		size;
	char	*instruction;

	while (ft_iswhitespace(input[*i]) == 1)
		*i = *i + 1;
	size = size_to_char(input, *i, ";");
	if (size == -1)
		return ;
	if (new_malloc((void **)&instruction, sizeof(char), size + 1) == 0)
		return ;
	cpy_instruction(instruction, input, i, size);
	*inst = instnew(ft_strdup(instruction));
	free(instruction);
	if (input[*i] == ';')
		*i = *i + 1;
}

void	exec_line(t_inst *inst, char *input, int *i)
{
	while (input[*i])
	{
		cut_input(&inst, input, i);
		cut_instruction(inst);
								print_debug(inst);
		if (inst->cmds->next == NULL)
		{
			if (inst->cmds->builtin > 0)
				;//simple_builtin();
			else
				exec_lonely_instruction(inst->cmds);
			instclear(inst);
		}
		else
		{
			exec_pipe(inst->cmds);
			instclear(inst);
		}
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
