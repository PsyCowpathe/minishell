/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:30:01 by agirona           #+#    #+#             */
/*   Updated: 2021/11/25 18:51:55 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_debug(t_inst *inst)
{
	t_inst	*current;
	t_cmd	*then;

	current = inst;
	while (current)
	{
		then = current->cmds;
		ft_putstr("instruction = ");
		ft_putstr(current->str);
		ft_putchar('\n');
		while (then)
		{
			ft_putstr("		command = ");
			ft_putstr(then->str);
			ft_putchar('\n');
			ft_putstr("		exec = ");
			ft_putstr(then->exec);
			ft_putchar('\n');
			then = then->next;
		}
		ft_putchar('\n');
		current = current->next;
	}
}
