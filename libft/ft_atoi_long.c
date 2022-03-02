/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:11:42 by acousini          #+#    #+#             */
/*   Updated: 2022/03/02 18:52:00 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi_long(const char *nptr)
{
	size_t		i;
	size_t		sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == '\n' || nptr[i] == ' ' || nptr[i] == '\f'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * sign);
}
