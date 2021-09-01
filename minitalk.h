/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylazrek <ylazrek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 16:25:58 by ylazrek           #+#    #+#             */
/*   Updated: 2021/08/31 17:28:26 by ylazrek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_msg
{
	unsigned char	c;
	size_t			size;
}				t_msg;

t_msg	g_msg;

size_t	ft_strlen(const char *str);
int		ft_strcmp(char *s1, char *s2);
void	handle(int sig);
int		is_num(const char *str);
int		compaire(const char *str, const char *max);
int		ft_atoi(const char *str);
void	send_sig(int pid, int sig);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putchar_fd(char c, int fd);

#endif
