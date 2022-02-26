/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:38:55 by agirona           #+#    #+#             */
/*   Updated: 2022/02/26 22:28:07 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//"$'tt'" il ecrit tout ce qu'il y a entre double quote //done
//'$tt' '"$tt"'  '$"tt"' il ecrit tout ce qu'il y a entre simple quote //done
//$tt normal //done
//"'$tt'" "$tt" il remplace et il garde les autres char quote compris//done
//$'tt' $"tt" il vire le dolar et ecrit le reste

char	*difficult_protocol(t_env *env, char *str, int *i, int state)
{
	char	*key;
	char	*res;

	if (state == 0 && str[*i] && ft_ischar("\r\n\v\t\f \'\"", str[*i]) == 1)
	{
		if (new_malloc((void *)&res, sizeof(char), 1) == 0)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	if (cpy_size_to_char(&key, str, i, "\r\n\v\t\f \'\"") != 1)
		return (NULL);
	state = search_key(env, key, &res);
	if (state == -1)
		return (NULL);
	if (state == 0)
	{
		if (new_malloc((void *)&res, sizeof(char), 1) == 0)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	return (res);
}

char	*simple_protocol(t_env *env, char *str, int *i, int state)
{
	char	*res;

	if (state == 2 || (state == 0 && !str[*i + 1])
		|| (state == 1 && (str[(*i) + 1] == '\"' || str[(*i) + 1] == '\'')))
	{
		if (new_malloc((void *)&res, sizeof(char), 1 + 1) == 0)
			return (NULL);
		res[0] = '$';
		res[1] = '\0';
		*i = *i + 1;
		return (res);
	}
	if (str[(*i) + 1] == '?' && ft_iswhitespace(str[(*i) + 2]) == 0)
	{
		*i = *i + 2;
		return (ft_itoa(g_pid_t[1024]));
	}
	*i = *i + 1;
	return (difficult_protocol(env, str, i, state));
}

char	*dollar_expand(char *str, t_env *env, int i, int d)
{
	int		state;
	char	*res;
	char	*full_res;

	state = 0;
	if (new_malloc((void *)&full_res, sizeof(char), ft_strlen(str) + 1) == 0)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			state = trigger(str[i], state);
			full_res[d++] = str[i++];
		}
		if (str[i] == '$')
		{
			res = simple_protocol(env, str, &i, state);
			if (res == NULL)
			{
				free(full_res);
				return ((char*)1);
			}
			if (res[0] == '\0')
			{
				full_res[0] = '\0';
				return (full_res);
			}
			if (join_all_part(res, &full_res, str, &d) == -2)
			{
				free(full_res);
				return ((char*)1);
			}
		}
		else if (str[i])
			full_res[d++] = str[i++];
	}
	return (dollar_expand_return_fucktion(full_res, d));
}
