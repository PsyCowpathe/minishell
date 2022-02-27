/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 04:29:14 by agirona           #+#    #+#             */
/*   Updated: 2022/02/27 04:39:55 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**exec_lonely_dependency(t_cmd *cmd)
{
	char	**env_tab;

	if (create_input_redirection(cmd) == -1
		|| create_output_redirection(cmd) == -1)
		exit(1);
	if (cmd->exec == NULL)
		exit(0);
	env_tab = build_env_tab(cmd);
	if (env_tab == NULL)
		exit(return_perror(1, "error ", ENOMEM));
	return (env_tab);
}

int	exec_last_dependency(t_cmd *cmd, pid_t cpid)
{
	set_pid(cpid);
	if (close(cmd->fd[0]) == -1)
		return (return_perror(-1, "error ", errno));
	if (close(cmd->fd[1]) == -1)
		return (return_perror(-1, "error ", errno));
	if (close(cmd->prev->fd[0]) == -1)
		return (return_perror(-1, "error ", errno));
	while (wait(&cpid) > 0)
		;
	g_pid_t[1024] = WEXITSTATUS(cpid);
	return (1);
}
