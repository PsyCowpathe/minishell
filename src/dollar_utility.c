/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:54:04 by agirona           #+#    #+#             */
/*   Updated: 2022/02/23 21:59:15 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	trigger(char c, int state)
{
	int		ret;

	ret = state;
	if (c == '\"' && state == 0)
		ret = 1;
	else if (c == '\"' && state == 1)
		ret = 0;
	else if (c == '\'' && state == 0)
		ret = 2;
	else if (c == '\'' && state == 2)
		ret = 0;
	return (ret);
}

int	search_key(t_env *env, char *key, char **res)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (env->set == 1)
			{
				*res = ft_strdup(env->value);
				return (1);
			}
			*res = NULL;
			return (0);
		}
		env = env->next;
	}
	*res = NULL;
	return (0);
}

void	join_all_part(char *res, char **full_res, char *str, int *d)
{
	char	*tmp;

	(*full_res)[*d] = '\0';
	tmp = ft_strjoin(*full_res, res);
	*d += ft_strlen(res);
	if (tmp[0] == '\0')
		*d = 0;
	free(res);
	free(*full_res);
	if (new_malloc((void **)full_res, sizeof(char), ft_strlen(str)
			+ ft_strlen(tmp) + 1) == 0)
		return ;//error
	ft_strncpy(*full_res, tmp, ft_strlen(tmp) + 1);
}

char	*dollar_expand_return_fucktion(char *full_res, int d)
{
	full_res[d] = '\0';
	//free(str);
	if (full_res[0] != '\0')
	{
		remove_quotes(full_res);
		return (full_res);
	}
	else
		return (NULL);
}
