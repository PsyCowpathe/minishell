/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:25 by agirona           #+#    #+#             */
/*   Updated: 2021/11/24 20:22:55 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_closed_quote(char *str, int i)
{
	char	c;

	c = str[i];
	i++;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		size_to_char(char *input, int i, char find)
{
	int		size;
	char	c;

	size = 0;
	while (input[i] && input[i] != find)
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			c = input[i];
			if (is_closed_quote(input, i) == 0)
			{
				ft_putstr("Error: Unclosed quotes\n");
				return (-1); //verifier strerror;
			}
			i++;
			size++;
			while (input[i] && input[i] != c)
			{
				i++;
				size++;
			}
		}
		size++;
		i++;
	}
	return (size);
}

void	cpy_instruction(char *dst, char *src, int *start, int size)
{
	int		end;
	int		i;

	end = *start + size;
	i = 0;
	while (*start < end)
	{
		dst[i] = src[*start];
		i++;
		*start = *start + 1;
	}
	dst[i] = '\0';
}

void	cut_instruction(t_inst *inst)
{
	int		i;
	char	*command;
	int		size;

	i = 0;
	while (1)
	{
		while (inst->str[i] && ft_iswhitespace(inst->str[i]) == 1)
			i++;
		size = size_to_char(inst->str, i, '|');
		if (size == -1)
			return ;
		if (new_malloc((void **)&command, sizeof(char), size + 1) == 0)
			return ;
		cpy_instruction(command, inst->str, &i, size);
		cmdadd_back(&inst->cmds, cmdnew(ft_strdup(command)));
		free(command);
		if (inst->str[i] == '|')
			i++;
		//cut_command(cmdlast((*inst)->cmds));
		if (inst->str[i] == '\0')
			break;
	}
}

void	exec_line(t_inst **inst, char *input, int *i)
{
	int		size;
	char	*instruction;

	while (1)
	{
		while (input[*i] && ft_iswhitespace(input[*i]) == 1)
			*i = *i + 1;
		size = size_to_char(input, *i, ';');
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
		if (input[*i] == '\0')
			break ;
	}
}

void	print_debug(t_inst *inst)
{
	t_inst	*current;
	t_cmd	*then;

	current = inst;
	while (current)
	{
		then = current->cmds;
		ft_putstr("instruction = ");
		ft_putstr(current->str);
		ft_putchar('\n');
		while (then)
		{
			ft_putstr("		command = ");
			ft_putstr(then->str);
			ft_putchar('\n');
			then = then->next;
		}
		ft_putchar('\n');
		current = current->next;
	}

}

int		main(void)
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
		exec_line(&inst, input, &i);
			print_debug(inst); //debug
		instclear(&inst);
	}
	return (0);
}
