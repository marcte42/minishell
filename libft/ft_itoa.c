/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:26:31 by acousini          #+#    #+#             */
/*   Updated: 2022/03/02 18:52:37 by acousini         ###   ########.fr       */
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

void	compose_string(int tmp, char *res, int size, int neg)
{
	int	i;

	i = 1;
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
}

char	*ft_itoa(int n)
{
	char			*res;
	int				size;
	int				neg;
	unsigned int	tmp;

	size = ft_size_itoa(n);
	neg = 0;
	if (n < 0)
		neg = 1;
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	tmp = n;
	if (n < 0)
		tmp = -n;
	compose_string(tmp, res, size, neg);
	return (res);
}
