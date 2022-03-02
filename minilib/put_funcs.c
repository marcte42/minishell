/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:46:11 by acousini          #+#    #+#             */
/*   Updated: 2022/03/02 18:53:55 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	long			nb;
	unsigned char	*ret;

	nb = n;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr(nb / 10);
	ret = (unsigned char *)(nb % 10 + 48);
	write(1, &ret, 1);
}

void	ft_putnbrnl(int nbr)
{
	ft_putnbr(nbr);
	ft_putchar('\n');
}

void	ft_putstr(char const *s)
{
	int		a;

	a = 0;
	if (!s)
		return ;
	while ((char)s[a])
	{
		write(1, (void *)&s[a], 1);
		++a;
	}
}

void	ft_putstr_fd(char const *s, int fd)
{
	int		a;

	a = 0;
	if (!s)
		return ;
	while ((char)s[a])
	{
		write(fd, (void *)&s[a], 1);
		++a;
	}
}
