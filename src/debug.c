/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoublai <agoublai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:30:01 by agirona           #+#    #+#             */
/*   Updated: 2021/12/17 15:57:49 by agirona          ###   ########lyon.fr   */
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
		ft_putstr("		valid = ");
		ft_putnbr(then->is_valid);
		ft_putchar('\n');
		ft_putstr("		command = ");
		ft_putstr(then->str);
		ft_putchar('\n');
		ft_putstr("		builtin =  ");
		ft_putnbr(then->builtin);
		ft_putchar('\n');
		ft_putstr("		exec =  ");
		ft_putstr(then->exec);
		ft_putchar('\n');
		ft_putstr("		redir in type =  ");
		ft_putnbr(then->redir_type[1]);
		ft_putchar('\n');
		ft_putstr("		redir in path =  ");
		ft_putstr(then->redir_in);
		ft_putchar('\n');
		ft_putstr("		redir out type =  ");
		ft_putnbr(then->redir_type[0]);
		ft_putchar('\n');
		ft_putstr("		redir out path =  ");
		ft_putstr(then->redir_out);
		ft_putchar('\n');
		if (then->echo_flag == 1)
		{
			ft_putstr("		flag =  1");
			ft_putchar('\n');
		}
		ft_putstr("		args =  ");
		while (then->is_valid == 1 && then->args[j])
		{
			if (j != 0)
				ft_putstr(" 			|");
			ft_putstr(then->args[j]);
			ft_putchar('|');
			ft_putchar('\n');
			j++;
		}
		then = then->next;
		ft_putchar('\n');
		ft_putchar('\n');
	}
	ft_putchar('\n');
}

/*void	print_path(char **path)
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
}*/
