/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:25 by agirona           #+#    #+#             */
/*   Updated: 2021/11/29 19:44:02 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_instruction(t_cmd *cmd)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
		execve(cmd->exec, cmd->args, g_envp);
	else
	{
		while ()
	}

do {
       pid_t tpid = wait(&child_status);
       if(tpid != child_pid) process_terminated(tpid);
     } while(tpid != child_pid);

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
