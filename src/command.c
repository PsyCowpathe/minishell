/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:35:29 by agirona           #+#    #+#             */
/*   Updated: 2021/11/25 18:51:54 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_flag(t_cmd *cmd, char *str, int i)
{
	int		save;
	char	quote;

	quote = 0;
	while (str[i] && ft_iswhitespace(str[i]) == 1)
		i = i + 1;
	save = i;
	if (str[i] == '"' || str[i] == '\'')
	{
		quote = str[i];
		i++;
	}
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		if ((quote && str[i + 2] == quote)
			|| (quote == 0 && ft_iswhitespace(str[i + 2]) == 1))
		{
			cmd->flag = 1;
			if (quote)
				i++;
			return (i + 2);
		}
	}
	return (save);
}

void	cut_exec(t_cmd *cmd, int *i)
{
	char	*fragment;
	int		size;

	size = size_to_char(cmd->str, *i, " \r\n\v\t\f");
	if (size == -1)
		return ;
	if (((cmd->str[*i] == '"' && cmd->str[size - 1] == '"')
			|| (cmd->str[*i] == '\'' && cmd->str[size - 1] == '\'')) && ++(*i))
		size -= 2;
	fragment = malloc(sizeof(char) * size);
	if (fragment == NULL)
		return ;
	cpy_instruction(fragment, cmd->str, i, size);
	cmd->exec = ft_strdup(fragment);
	free(fragment);
	if (ft_strcmp(cmd->exec, "echo") == 0)
		*i = is_flag(cmd, cmd->str, *i);
	ft_putstr("flag = ");
	ft_putnbr(cmd->flag);
	ft_putchar('\n');
}

void	cut_command(t_cmd *cmd)
{
	int		i;

	i = 0;
	cut_exec(cmd, &i);
}
