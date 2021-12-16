/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:25 by agirona           #+#    #+#             */
/*   Updated: 2021/12/16 16:15:32 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *const	*g_envp = NULL;

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
		print_debug(inst); //delete
		if (inst->cmds->next == NULL)
		{
			if (inst->cmds->builtin > 0)
			{
				ft_putstr("c'est pas imped menther du con\n");
				//simple_builtin();
			}
			else
				exec_lonely(inst->cmds);
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

	if (argc && argv) // delete
		i = 0;
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
