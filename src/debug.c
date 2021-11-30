/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:30:01 by agirona           #+#    #+#             */
/*   Updated: 2021/11/30 16:05:59 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_debug(t_inst *inst)
{
	t_cmd	*then;
	int		j;

	then = inst->cmds;
	ft_putstr("instruction = ");
	ft_putstr(inst->str);
	ft_putchar('\n');
	while (then)
	{
		j = 0;
		ft_putstr("		command = ");
		ft_putstr(then->str);
		ft_putchar('\n');
		ft_putstr("		builtin =  ");
		ft_putnbr(then->builtin);
		ft_putchar('\n');
		ft_putstr("		exec =  ");
		ft_putstr(then->exec);
		ft_putchar('\n');
		if (then->echo_flag == 1)
		{
			ft_putstr("		flag =  1");
			ft_putchar('\n');
		}
		ft_putstr("		args =  ");
		while (then->args[j])
		{
			if (j != 0)
				ft_putstr("			");
			ft_putstr(then->args[j]);
			ft_putchar('\n');
			j++;
		}
		then = then->next;
	}
	ft_putchar('\n');
}

void	print_path(char **path)
{
	int		i;

	i = 0;
	while (path[i])
	{
		ft_putstr(path[i]);
		ft_putchar('\n');
		i++;
	}
}

void	print_env(void)
{
	int		i;

	i = 0;
	while (g_envp[i])
	{
		ft_putstr(g_envp[i]);
		ft_putchar('\n');
		i++;
	}
}
