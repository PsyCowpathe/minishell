/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:11:52 by agirona           #+#    #+#             */
/*   Updated: 2022/02/22 20:48:12 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handler(int signum)
{
	int		i;

	i = 0;
	if (signum == 2)
	{
		while (i < 1024 && g_pid_t[i] != 0)
		{
			g_pid_t[i] = 0;
			i++;
		}
		if (i == 0) 
		{
			ft_putstr("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (signum == 3)
	{
		write(1, "tg", 2); //dooo it
		exit(0);
	}
}

void	signals(void)
{
	struct sigaction sa;

	sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART; 
    if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		;//
	}
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
        /* Handle error */;
	}
}
