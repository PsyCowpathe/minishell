/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:30:33 by agirona           #+#    #+#             */
/*   Updated: 2021/11/30 16:59:28 by agirona          ###   ########lyon.fr   */
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
