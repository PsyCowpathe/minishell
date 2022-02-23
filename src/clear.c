/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:45:41 by agirona           #+#    #+#             */
/*   Updated: 2022/02/23 21:59:12 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envtab_clear(char **env_tab)
{
	int	j;

	j = 0;
	if (env_tab)
	{
		while (env_tab[j])
		{
			free(env_tab[j]);
			j++;
		}
		free(env_tab);
		env_tab = NULL;
	}
}

void	cmd_clear(t_cmd *cmd)
{
	int		i;

	i = 1;
	if (cmd->ret)
		free(cmd->ret);
	if (cmd->str)
		free(cmd->str);
	if (cmd->exec)
		free(cmd->exec);
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			if (cmd->args[i])
				free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->redir_in)
		free(cmd->redir_in);
	if (cmd->redir_out)
		free(cmd->redir_out);
	free(cmd);
}

void	env_clear(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		if (env->str)
			free(env->str);
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = next;
	}
}
