/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:32:53 by agirona           #+#    #+#             */
/*   Updated: 2022/02/26 18:31:54 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_lst(char *const envp[])
{
	int		i;
	t_env	*env;
	t_env	*tmp;

	i = 0;
	if (envp[i])
	{
		env = envnew(ft_strdup(envp[i++]));
		if (env == NULL)
			return (NULL);
	}
	while (envp[i])
	{
		tmp = envnew(ft_strdup(envp[i++]));
		if (tmp == NULL)
		{
			envclear(&env);
			return (NULL);
		}
		envadd_back(&env, tmp);
	}
	return (env);
}

t_env	*envnew(char *str)
{
	t_env	*new;
	int		d;

	d = 0;
	if (str == NULL || new_malloc((void *)&new, sizeof(t_env), 1) == 0)
	{
		if (str != NULL)
			free(str);
		return_perror(0, "error ", ENOMEM);
		return (NULL);
	}
	new->str = str;
	if (cpy_size_to_char(&new->key, new->str, &d, "=") != 1)
	{
		envclear(&new);
		return (NULL);
	}
	d++;
	if (cpy_size_to_char(&new->value, new->str, &d, "\0") != 1)
	{
		envclear(&new);
		return (NULL);
	}
	new->set = 1;
	new->next = NULL;
	return (new);
}

t_env	*envlast(t_env *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
		{
			lst = lst->next;
		}
	}
	return (lst);
}

void	envadd_back(t_env **alst, t_env *new)
{
	t_env	*last;

	if (!*alst)
		*alst = new;
	else
	{
		last = envlast(*alst);
		last->next = new;
	}
}

void	envclear(t_env **lst)
{
	t_env	*next;

	while (*lst)
	{
		next = (*lst)->next;
		if ((*lst)->key)
			free((*lst)->str);
		if ((*lst)->key)
			free((*lst)->key);
		if ((*lst)->value)
			free((*lst)->value);
		free(*lst);
		*lst = next;
	}
}
