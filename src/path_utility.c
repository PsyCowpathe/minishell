/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:43:42 by agirona           #+#    #+#             */
/*   Updated: 2022/02/27 02:52:14 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_count(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == ':')
			count++;
		i++;
	}
	return (count);
}

char	*join_path(char *exec, char *path)
{
	char	*new_exec;
	char	*ret;
	char	*tmp;

	new_exec = ft_strtrim(exec, "\"\'");
	if (new_exec == NULL)
		return (NULL);
	tmp = ft_strjoin("/", new_exec);
	free(new_exec);
	if (tmp == NULL)
		return (NULL);
	ret = ft_strjoin(path, tmp);
	free(tmp);
	if (ret == NULL)
		return (NULL);
	return (ret);
}
