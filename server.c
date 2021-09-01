/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylazrek <ylazrek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 19:33:22 by ylazrek           #+#    #+#             */
/*   Updated: 2021/08/31 17:29:12 by ylazrek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle(int sig)
{
	unsigned char	off_bit;

	if (sig == SIGUSR1)
	{
		if (g_msg.size < 8)
		{
			g_msg.c = g_msg.c | (0x1 << g_msg.size);
			++g_msg.size;
		}
	}
	else if (sig == SIGUSR2)
	{
		if (g_msg.size < 8)
		{
			off_bit = 0xFF ^ (0x01 << g_msg.size);
			g_msg.c = g_msg.c & (off_bit);
			++g_msg.size;
		}
	}
	if (g_msg.size == 8)
	{
		g_msg.size = 0;
		write(1, &g_msg.c, 1);
		g_msg.c = 0x0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	act;

	if (ac == 1)
	{
		(void)av;
		ft_putnbr_fd(getpid(), 1);
		write(1, "\n", 1);
		g_msg.c = 0x0;
		g_msg.size = 0;
		act.__sigaction_u.__sa_handler = handle;
		sigemptyset(&act.sa_mask);
		act.sa_flags = SA_RESTART;
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		while (1)
			pause();
	}
	else
		write(1, "Error: argument\n", 16);
	return (0);
}
