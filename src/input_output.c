/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:11:08 by agirona           #+#    #+#             */
/*   Updated: 2022/02/27 04:42:24 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc_redirection_dependency(int fd)
{
	if (close(fd) == -1)
		return (return_perror(-1, "error ", errno));
	fd = open(".heredoc.tmp", O_RDONLY, 0644);
	if (fd == -1)
		return (return_perror(-1, "error ", errno));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (return_perror(-1, "error ", errno));
	if (close(fd) == -1)
		return (return_perror(-1, "error ", errno));
	if (unlink(".heredoc.tmp") == -1)
		return (return_perror(-1, "error ", errno));
	return (1);
}

int	create_heredoc_redirection(t_cmd *cmd)
{
	int		fd;
	char	*input;

	fd = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (return_perror(-1, "error ", errno));
	input = readline("> ");
	if (input == NULL)
	{
		if (close(fd) == -1)
			return (return_perror(-1, "error ", errno));
		if (unlink(".heredoc.tmp") == -1)
			return (return_perror(-1, "error ", errno));
	}
	while (ft_strcmp(input, cmd->redir_in) != 0)
	{
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		input = readline("> ");
	}
	if (create_heredoc_redirection_dependency(fd) == -1)
		return (-1);
	return (0);
}

int	create_input_redirection(t_cmd *cmd)
{
	int		fd;

	if (cmd->redir_type[1] == 2)
	{
		fd = open(cmd->redir_in, O_RDONLY);
		if (fd == -1)
			return (return_perror(-1, "error ", errno));
		if (dup2(fd, STDIN_FILENO) == -1)
			return (return_perror(-1, "error ", errno));
		if (close(fd) == -1)
			return (return_perror(-1, "error ", errno));
		return (0);
	}
	else if (cmd->redir_type[1] == 1)
		return (create_heredoc_redirection(cmd));
	return (0);
}

int	create_output_redirection(t_cmd *cmd)
{
	int		fd;

	if (cmd->redir_type[0] == 3)
	{
		fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (return_perror(-1, "error ", errno));
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (return_perror(-1, "error ", errno));
		if (close(fd) == -1)
			return (return_perror(-1, "error ", errno));
		return (0);
	}
	else if (cmd->redir_type[0] == 4)
	{
		fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (return_perror(-1, "error ", errno));
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (return_perror(-1, "error ", errno));
		if (close(fd) == -1)
			return (return_perror(-1, "error ", errno));
		return (0);
	}
	return (0);
}
