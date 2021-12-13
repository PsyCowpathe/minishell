/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:35:29 by agirona           #+#    #+#             */
/*   Updated: 2021/12/13 19:28:09 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_echo_flag(t_cmd *cmd, char *str, int i)
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
		if ((quote && str[i + 2] == quote) || (quote == 0 && (str[i + 2] == '\0'
						|| ft_iswhitespace(str[i + 2]) == 1)))
		{
			cmd->echo_flag = 1;
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
	
	while (ft_iswhitespace(cmd->str[*i]))
		(*i)++;
	size = size_to_char(cmd->str, *i, " \r\n\v\t\f");
	if (size == -1)
		return ;
	fragment = malloc(sizeof(char) * (size + 1));
	if (fragment == NULL)
		return ;
	cpy_instruction(fragment, cmd->str, i, size);
	cmd->exec = ft_strdup(fragment);
	free(fragment);
}

void	get_args(t_cmd *cmd, int i)
{
	int		j;
	int		size;

	cmd->args = malloc(sizeof(char *) * (count_args(cmd->str, i) + 2));
	if (cmd->args == NULL)
		return ;
	j = 1;
	cmd->args[0] = malloc(sizeof(char) * 1); 
	if (cmd->args[0] == NULL)
		return ;
	cmd->args[0][0] = '\0';
	while (ft_iswhitespace(cmd->str[i]) == 1)
		i++;
	while (cmd->str[i])
	{
		while (cut_redir(cmd, &i))
			;
		while (ft_iswhitespace(cmd->str[i]) == 1)
			i++;
		size = size_to_char(cmd->str, i, " \r\n\v\t\f");
		if (size == 0)
		{
			cmd->args[j] = NULL;
			return ;
		}
		cmd->args[j] = malloc(sizeof(char) * size);
		if (cmd->args[j] == NULL)
			return ;
		cpy_instruction(cmd->args[j], cmd->str, &i, size);
		j++;
	}
	cmd->args[j] = NULL;
}

void	cut_command(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (ft_iswhitespace(cmd->str[i]) == 1)
		i++;
	while (cut_redir(cmd, &i))
		;
	cut_exec(cmd, &i);
	if (strcmp_quote(cmd->exec, "echo") == 1)
		i = get_echo_flag(cmd, cmd->str, i);
	cmd->builtin = is_builtin(cmd);
	get_args(cmd, i);
}
