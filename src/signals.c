/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:11:52 by agirona           #+#    #+#             */
/*   Updated: 2022/02/23 21:59:13 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_forked(void)
{
	rl_on_new_line();
	rl_redisplay();
	write(2, "  \b\b", 4);
	ft_putstr("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler(void)
{
	int		i;
	int		trigger;

	i = 0;
	trigger = 0;
	while (i < 1024 && g_pid_t[i] != 0)
	{
		trigger = 1;
		i++;
	}
	i--;
	while (trigger == 1 && i >= 0)
	{
		kill(g_pid_t[i], SIGTERM);
		g_pid_t[i--] = 0;
	}
	if (trigger == 1)
		ft_putchar('\n');
	if (trigger == 0)
		no_forked();
}

void	sigquit_handler(void)
{
	int		i;
	int		trigger;
	int		reach;

	i = 0;
	trigger = 0;
	reach = 0;
	if (access(".heredoc.tmp", R_OK))
		reach = 1;
	while (g_pid_t[i] != 0)
	{
		trigger = 1;
		i++;
	}
	if (i > 0 && reach == 1)
		g_pid_t[i - 1] = 0;
	if (i != 0 && reach == 1)
		ft_putstr_fd("Quit: 3\n", 2);
	else if (trigger == 0)
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "  \b\b", 4);
	}
}

static void	handler(int signum)
{
	if (signum == 2)
		sigint_handler();
	else if (signum == 3)
		sigquit_handler();
}

void	signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		; //error
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		;//error
}
