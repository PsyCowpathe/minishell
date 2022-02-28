/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 03:05:22 by agirona           #+#    #+#             */
/*   Updated: 2022/02/28 03:06:57 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_flag(t_cmd *cmd)
{
	int		flag;

	flag = 1;
	if (ft_strcmp(cmd->args[1], "-n") == 0)
		flag = 2;
	return (flag);
}

int	exec_echo(t_cmd *cmd, int i, int fd, int flag)
{
	if (cmd->args[1] == NULL)
		return (0);
	flag = echo_flag(cmd);
	i = flag;
	while (cmd->args[i])
	{
		if (cmd->redir_out != NULL)
			fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = STDOUT_FILENO;
		if (fd == -1)
			return (return_perror(-2, "error ", errno));
		ft_putstr_fd(cmd->args[i], fd);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (flag == 1)
		ft_putchar_fd('\n', fd);
	if (fd != STDOUT_FILENO && close(fd) == -1)
		return (return_perror(-2, "error ", errno));
	return (1);
}
