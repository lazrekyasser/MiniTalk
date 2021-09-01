/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylazrek <ylazrek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 16:49:09 by ylazrek           #+#    #+#             */
/*   Updated: 2021/08/31 17:27:58 by ylazrek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	unsigned int	num;
	int				i;
	int				np;

	np = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			np = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(np * num));
}

int	is_num(const char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (str[0] == '+' && ft_strlen(str) == 1)
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
		cnt++;
	}
	if (cnt > 10)
		return (0);
	else if (cnt == 10)
		return (compaire(str, "2147483647"));
	return (1);
}

void	send_sig(int pid, int sig)
{
	if (kill(pid, sig) == -1)
	{
		write(1, "Error: PID not found\n", 21);
		exit(1);
	}
}

void	ft_send(int pid, char **av, unsigned char mask)
{
	int				i;
	int				j;
	unsigned char	c;

	i = 0;
	while (av[2][i])
	{
		c = av[2][i];
		j = 0;
		while (j < 8)
		{
			if ((c & mask) == mask)
				send_sig(pid, SIGUSR1);
			else if ((c & mask) == 0x0)
				send_sig(pid, SIGUSR2);
			mask = mask << 1;
			j++;
			usleep(75);
		}
		mask = 0x01;
		i++;
		usleep(75);
	}
}

int	main(int ac, char **av)
{
	int				pid;
	unsigned char	mask;

	if (ac == 3)
	{
		if (is_num(av[1]) && ft_strcmp(av[2], ""))
		{
			pid = ft_atoi(av[1]);
			if (pid < 100 || pid > 99998)
				return (1);
			mask = 0x01;
			ft_send(pid, av, mask);
		}
		else
			write(1, "Error: argument\n", 16);
	}
	else
		write(1, "Error: argument\n", 16);
	return (0);
}
