/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:25 by agirona           #+#    #+#             */
/*   Updated: 2021/11/23 18:47:05 by agirona          ###   ########lyon.fr   */
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

int		size_instruction(char *input, int i)
{
	int		size;
	char	c;

	size = 0;
	while (input[i] && input[i] != ';')
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

void	get_instruction(t_inst **inst, char *input, int *i)
{
	int		size;
	char	*instruction;

	while (1)
	{
		while (ft_iswhitespace(input[*i]) == 1)
			*i = *i + 1;
		size = size_instruction(input, *i);
		if (size == -1)
			return ;
		if (new_malloc((void **)&instruction, sizeof(char), size + 1) == 0)
			return ;
		cpy_instruction(instruction, input, i, size);
		instadd_back(inst, instnew(ft_strdup(instruction)));
		if (input[*i] == ';')
			*i = *i + 1;
		if (input[*i] == '\0')
			break ;
		free(instruction);
	}
}

int		main(void)
{
	int		exec_ret;
	char	*input;
	int		i;
	t_inst	*inst;

	exec_ret = 0;
	while (exec_ret == 0)
	{
		i = 0;
		input = readline("minishell$> ");
		get_instruction(&inst, input, &i);
		instclear(&inst);
	}
	return (0);
}
