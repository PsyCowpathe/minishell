/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:38:11 by agirona           #+#    #+#             */
/*   Updated: 2022/02/10 18:45:18 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_count(t_env *env)
{
	int		count;
	t_env	*save;

	save = env;
	count = 1;
	while (env)
	{
		if (env->set == 1)
			count++;
		env = env->next;
	}
	env = save;
	return (count);
}

char	**build_env_tab(t_cmd *cmd)
{
	char	**res;
	int		i;
	t_env	*save;

	res = malloc(sizeof(char *) * (env_count(cmd->env) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	save = cmd->env;
	while (cmd->env)
	{
		if (cmd->env->set == 1)
			res[i++] = ft_strdup(cmd->env->str);
		cmd->env = cmd->env->next;
	}
	res[i] = NULL;
	cmd->env = save;
	return (res);
}
