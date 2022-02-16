/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:30:33 by agirona           #+#    #+#             */
/*   Updated: 2022/02/16 15:35:07 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_closed_quote(char *str, int i)
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

int	size_to_char(char *input, int i, char *find)
{
	int		size;
	char	c;

	size = 0;
	while (input[i] && ft_ischar(find, input[i]) == 0)
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
			while (input[i] && input[i] != c && ++i)
				size++;
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
	while (src[*start] && *start < end)
	{
		dst[i] = src[*start];
		i++;
		*start = *start + 1;
	}
	dst[i] = '\0';
}

int	cpy_size_to_char(char **dst, char *src, int *start, char *search)
{
	int		size;

	size = size_to_char(src, *start, search);
	if (size == -1)
		return (-14);
	*dst = malloc(sizeof(char) * (size + 1));
	if (*dst == NULL)
		return (-1);
	cpy_instruction(*dst, src, start, size);
	return (1);
}
