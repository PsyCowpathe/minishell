/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:23:46 by agirona           #+#    #+#             */
/*   Updated: 2022/02/27 04:37:52 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_error(int ret)
{
	if (ret == -1)
		ft_putstr_fd("error : Unclosed quotes\n", 2);
	else if (ret == -2)
		ft_putstr_fd("Error: redirection\n", 2);
	else if (ret == -3)
		ft_putstr_fd("Error: cant unlink .heredoc.tmp\n", 2);
	else
		ft_putstr_fd("pas encore gerer", 2);
	if (ret == -4)
		ft_putstr("Error: J'ai po reussi a creer :(\n");
	if (ret == -18)
		ft_putstr("Error: J'ai pas reussi a creer\n");
	return (ret);
}

int	return_perror(int ret, char *msg, int code)
{
	errno = code;
	perror(msg);
	return (ret);
}
