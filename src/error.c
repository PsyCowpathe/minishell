/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:23:46 by agirona           #+#    #+#             */
/*   Updated: 2022/02/23 21:59:17 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		return_error(int ret)
{
	if (ret == -3)
		ft_putstr("Error: J'ai po reussi a creer :(\n");
	else if (ret == -18)
		ft_putstr("Error: J'ai pas reussi a creer\n");
	return (ret);
}
