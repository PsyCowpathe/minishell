/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 02:49:08 by agirona           #+#    #+#             */
/*   Updated: 2022/02/28 03:06:58 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	psm(t_cmd *cmd, char ***tab, int *i)
{
	if (cmd->args[1] == NULL)
		return (1);
	*tab = ft_split(cmd->args[1], '=');
	if (*tab == NULL)
		return (return_perror(-1, "error ", ENOMEM));
	*i = 2;
	if (!tab[0][0] || !tab[0][1])
	{
		envtab_clear(*tab);
		return (1);
	}
	return (0);
}

int	exec_export_dependency(t_cmd *cmd, t_env *env, char **tab)
{
	if (env->key == tab[0])
	{
		free(env->value);
		env->value = tab[1];
		envtab_clear(tab);
		free(env->str);
		env->str = ft_strdup(cmd->args[1]);
		if (env->str == NULL)
			return (return_perror(-1, "error ", ENOMEM));
		return (1);
	}
	return (0);
}

int	nsm(char **tab, int *i)
{
	char	*tmp;

	tmp = ft_strjoin(tab[1], "=");
	if (tmp == NULL)
	{
		envtab_clear(tab);
		return (return_perror(-1, "error ", ENOMEM));
	}
	tab[1] = ft_strjoin(tmp, tab[(*i)++]);
	free(tmp);
	if (tab[1] == NULL)
	{
		envtab_clear(tab);
		return (return_perror(-1, "error ", ENOMEM));
	}
	return (0);
}

int	exec_export(t_cmd *cmd, int i, int ret)
{
	char	**tab;
	t_env	*env;
	char	*tmp;

	ret = psm(cmd, &tab, &i);
	if (ret == 1 || ret == -1)
		return (ret);
	while (tab[i])
		if (nsm(tab, &i) == -1)
			return (-1);
	env = cmd->env;
	while (env)
	{
		ret = exec_export_dependency(cmd, env, tab);
		if (ret == 1 || ret == -1)
			return (ret);
		env = env->next;
	}
	envtab_clear(tab);
	tmp = ft_strdup(cmd->args[1]);
	if (tmp == NULL)
		return (return_perror(-1, "error ", ENOMEM));
	envadd_back(&cmd->env, envnew(tmp));
	return (1);
}
