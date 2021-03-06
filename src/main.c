/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:25 by agirona           #+#    #+#             */
/*   Updated: 2022/02/28 03:19:20 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid_t[1025] = {0};

int	cut_input(t_inst **inst, char *input, int *i)
{
	int		size;
	char	*instruction;

	while (ft_iswhitespace(input[*i]) == 1)
		*i = *i + 1;
	if (input[*i] == '\0')
		return (0);
	size = size_to_char(input, *i, ";");
	if (size == -1)
		return (0);
	if (new_malloc((void **)&instruction, sizeof(char), size + 1) == 0)
		return (-1);
	cpy_instruction(instruction, input, i, size);
	*inst = instnew(instruction);
	if (*inst == NULL)
	{
		free(instruction);
		return (-1);
	}
	if (input[*i] == ';')
		*i = *i + 1;
	return (1);
}

int	exec_line_dependency(t_inst *inst)
{
	int		ret;

	if (inst->cmds->builtin > 0)
	{
		ret = simple_builtin(inst->cmds);
		if (ret != 1)
			return (ret);
	}
	else if (exec_lonely(inst->cmds) == -1)
	{
		instclear(inst);
		return (-1);
	}
	return (1023);
}

int	exec_line(t_inst *inst, char *input, int *i, t_env *env)
{
	int		ret;

	while (input[*i])
	{
		ret = cut_input(&inst, input, i);
		if (ret != 1)
			return (instclear_return(inst, ret));
		ret = cut_instruction(inst, env, 0, 0);
		if (ret != 1)
			return (instclear_return(inst, ret));
		if (inst->cmds->next == NULL)
		{
			ret = exec_line_dependency(inst);
			if (ret != 1023)
				return (ret);
		}
		else if (exec_pipe(inst->cmds) == -1)
			return (instclear_return(inst, -1));
		instclear(inst);
	}
	return (1);
}

void	minishell(t_env *env)
{
	t_inst	inst;
	int		i;
	int		exec_ret;
	char	*input;

	exec_ret = 0;
	while (exec_ret == 0)
	{
		init_pid();
		i = 0;
		input = readline("minishell$> ");
		if (input == NULL)
			exec_ret = 1;
		else if (input[0])
			add_history(input);
		if (input && input[0])
			if (exec_line(&inst, input, &i, env) == -1)
				exec_ret = 1;
		free(input);
	}
}

int	main(int argc, char **argv, char *const envp[])
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = create_env_lst(envp);
	if (env == NULL)
		return (1);
	if (signals() != 1)
	{
		env_clear(env);
		return (1);
	}
	minishell(env);
	if (env)
		env_clear(env);
	rl_clear_history();
	return (0);
}
