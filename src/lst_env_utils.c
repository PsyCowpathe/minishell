/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:32:53 by agirona           #+#    #+#             */
/*   Updated: 2022/02/23 21:59:11 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_lst(char *const envp[])
{
	int		i;
	t_env	*env;

	i = 0;
	if (envp[i])
		env = envnew(ft_strdup(envp[i++]));
	while (envp[i])
		envadd_back(&env, envnew(ft_strdup(envp[i++])));
	return (env);
}

t_env	*envnew(char *str)
{
	t_env	*new;
	int		d;

	d = 0;
	if (new_malloc((void *)&new, sizeof(t_env), 1) == 0)
		return (NULL);
	new->str = str;
	cpy_size_to_char(&new->key, new->str, &d, "=");
	d++;
	cpy_size_to_char(&new->value, new->str, &d, "\0");
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
