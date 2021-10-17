/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pravry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 14:26:31 by pravry            #+#    #+#             */
/*   Updated: 2019/12/08 17:53:28 by pravry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_itoa(int n)
{
	int		size;

	size = 0;
	if (n < 0 && n != -2147483648)
	{
		size++;
		n = -n;
	}
	else if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (11);
	while (n >= 1)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char		*ft_itoa(int n)
{
	char			*res;
	int				i;
	int				size;
	int				neg;
	unsigned int	tmp;

	size = ft_size_itoa(n);
	neg = (n < 0 ? 1 : 0);
	i = 1;
	if (!((res = (char *)malloc(sizeof(char) * (size + 1)))))
		return (NULL);
	tmp = (n < 0 ? -n : n);
	if (tmp == 0)
		res[0] = '0';
	while (tmp >= 1)
	{
		res[size - i] = (tmp % 10) + '0';
		tmp = tmp / 10;
		i++;
	}
	if (neg == 1)
		res[0] = '-';
	res[size] = '\0';
	return (res);
}
