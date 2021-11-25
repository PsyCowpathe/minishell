/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:25 by agirona           #+#    #+#             */
/*   Updated: 2021/11/25 18:51:53 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_line(t_inst **inst, char *input, int *i)
{
	int		size;
	char	*instruction;

	while (input[*i])
	{
		while (input[*i] && ft_iswhitespace(input[*i]) == 1)
			*i = *i + 1;
		size = size_to_char(input, *i, ";");
		if (size == -1)
			return ;
		if (new_malloc((void **)&instruction, sizeof(char), size + 1) == 0)
			return ;
		cpy_instruction(instruction, input, i, size);
		instadd_back(inst, instnew(ft_strdup(instruction)));
		free(instruction);
		if (input[*i] == ';')
			*i = *i + 1;
		cut_instruction(instlast(*inst));
	}
}

int	main(void)
{
	int		exec_ret;
	char	*input;
	int		i;
	t_inst	*inst;

	exec_ret = 0;
	inst = NULL;
	while (exec_ret == 0)
	{
		i = 0;
		input = readline("minishell$> ");
		add_history(input);
		exec_line(&inst, input, &i);
		print_debug(inst); //debug
		instclear(&inst);
	}
	//rl_clear_history();
	return (0);
}
