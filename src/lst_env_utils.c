/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:32:53 by agirona           #+#    #+#             */
/*   Updated: 2021/12/17 15:57:59 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_env_lst(t_env **env, char *const envp[])
{
	int		i;
	int		d;

	i = 0;
	if (envp[i])
		*env = envnew(ft_strdup(envp[i++]));
	while (envp[i])
		envadd_back(env, envnew(ft_strdup(envp[i++])));
	while (*env)
	{
		d = 0;
		cpy_size_to_char(&(*env)->key, (*env)->str, &d, "=");
		d++;
		cpy_size_to_char(&(*env)->value, (*env)->str, &d, "\0");
		env = &(*env)->next;
	}
}

t_env	*envnew(char *str)
{
	t_env	*new;

	if (new_malloc((void *)&new, sizeof(t_env), 1) == 0)
		return (NULL);
	new->str = str;
	new->key = NULL;
	new->value = NULL;
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
