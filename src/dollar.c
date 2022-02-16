/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:38:55 by agirona           #+#    #+#             */
/*   Updated: 2022/02/16 15:35:05 by agirona          ###   ########lyon.fr   */
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
			return (NULL); //error
		res[0] = '\0';
		return (res);
	}
	if (cpy_size_to_char(&key, str, i, "\r\n\v\t\f \'\"") != 1)
	{
		return (NULL); //error
	}
	if (search_key(env, key, &res) == 0)
	{
		if (new_malloc((void *)&res, sizeof(char), 1) == 0)
			return (NULL); //error
		res[0] = '\0';
		return (res);
	}
	return (res);
}

char	*simple_protocol(t_env *env, char *str, int *i, int state)
{
	char	*res;

	if (state == 2
		|| (state == 1 && (str[(*i) + 1] == '\"' || str[(*i) + 1] == '\'')))
	{
		if (new_malloc((void *)&res, sizeof(char), 1 + 1) == 0)
			return (NULL); //error
		res[0] = '$';
		res[1] = '\0';
		*i = *i + 1;
		return (res);
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
		return (NULL); //error
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
			join_all_part(res, &full_res, str, &d);
		}
		else if (str[i])
			full_res[d++] = str[i++];
	}
	return (dollar_expand_return_fucktion(full_res, str, d));
}
