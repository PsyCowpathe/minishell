/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:21:48 by agirona           #+#    #+#             */
/*   Updated: 2022/02/28 01:27:04 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shift(char *str, int i)
{
	while (str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
}

void	remove_quotes(char *str)
{
	int		trigger;
	int		i;

	i = 0;
	trigger = 0;
	while (str[i])
	{
		if (trigger == 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			if (str[i] == '\'')
				trigger = 1;
			else
				trigger = 2;
			shift(str, i);
		}
		else if ((trigger == 1 && str[i] == '\'')
			|| (trigger == 2 && str[i] == '\"'))
		{
			shift(str, i);
			trigger = 0;
		}
		else
			i++;
	}
}
