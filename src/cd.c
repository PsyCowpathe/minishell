/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 22:41:59 by agirona           #+#    #+#             */
/*   Updated: 2022/02/28 03:06:59 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	moov_pwd(t_cmd *cmd, char *new, char *pwd)
{
	t_env	*current;
	int		ret;

	ret = access(new, F_OK);
	if (ret == -1)
		return (return_perror(-1, "error ", errno));
	if (ret == 0)
	{
		if (chdir(new) == -1)
			return (return_perror(-1, "error ", errno));
		current = cmd->env;
		while (current && ft_strcmp("OLDPWD", current->key) != 0)
			current = current->next;
		free(current->value);
		current->value = pwd;
		current = cmd->env;
		while (current && ft_strcmp("PWD", current->key) != 0)
			current = current->next;
		free(current->value);
		current->value = getcwd(NULL, 0);
		if (current->value == NULL)
			return (return_perror(-1, "error ", ENOMEM));
	}
	return (1);
}

int	cd(t_cmd *cmd, char *path, char *pwd)
{
	char	*new;
	char	*tmp;

	if (path[0] != '/')
	{
		tmp = ft_strjoin(pwd, "/");
		if (tmp == NULL)
			return (return_perror(-1, "error ", ENOMEM));
		new = ft_strjoin(tmp, path);
		free(tmp);
		if (new == NULL)
			return (return_perror(-1, "error ", ENOMEM));
	}
	else
		new = path;
	moov_pwd(cmd, new, pwd);
	return (1);
}

char	*getvalue(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current && ft_strcmp(key, current->key) != 0)
		current = current->next;
	if (current == NULL)
		return (NULL);
	return (current->value);
}

int	exec_cd(t_cmd *cmd)
{
	char	*pwd;
	int		ret;

	ret = 1;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (return_perror(-2, "error ", ENOMEM));
	if (cmd->args[1] == NULL)
		ret = moov_pwd(cmd, getvalue(cmd->env, "HOME"), pwd);
	else
		ret = cd(cmd, cmd->args[1], pwd);
	return (ret);
}
