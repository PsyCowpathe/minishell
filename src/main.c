/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:25 by agirona           #+#    #+#             */
/*   Updated: 2022/02/22 20:48:17 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (-1);
	if (new_malloc((void **)&instruction, sizeof(char), size + 1) == 0)
		return (-1);
	cpy_instruction(instruction, input, i, size);
	*inst = instnew(instruction);
	if (input[*i] == ';')
		*i = *i + 1;
	return (1);
}

void	exec_line(t_inst *inst, char *input, int *i, t_env *env)
{
	while (input[*i])
	{
		if (cut_input(&inst, input, i) != 1)
			return ;
		if (cut_instruction(inst, env) != 1)
			return ;
		//builting_detection;
		//print_debug(inst); //deletee
		if (inst->cmds->next == NULL)
		{
			if (inst->cmds->builtin > 0)
				simple_builtin(inst->cmds);
			else
				exec_lonely(inst->cmds, inst);
			instclear(inst);
		}
		else
		{
			exec_pipe(inst->cmds);
			instclear(inst);
		}
	}
}

void	env_clear(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		if (env->str)
			free(env->str);
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = next;
	}
}

int	main(int argc, char **argv, char *const envp[])
{
	int		exec_ret;
	char	*input;
	int		i;
	int		d;
	t_inst	inst;
	t_env	*env;

	(void)argc;
	(void)argv;
	exec_ret = 0;
	env = create_env_lst(envp);
	signals();
	d = 0;
	while (exec_ret == 0)
	{
		init_pid(); //faudra split
		d++;
		i = 0;
		input = readline("minishell$> ");
		if (input == NULL)
			exec_ret = 1;
		add_history(input);
		if (input)
			exec_line(&inst, input, &i, env);
		free(input);
	}
	if (env)
		env_clear(env);
	//rl_clear_history();
	return (0);
}
