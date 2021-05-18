/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:27:17 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/14 15:28:51 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_three.h"

int	check_valid_simbol(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\v' || str[i] == '\n')
		i++;
	return (i);
}

int	check_overflow(int digit, int minus)
{
	if (digit > 20)
	{
		if (minus == 1)
			return (-1);
		return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long long int	nb;
	int				minus;
	int				k;

	nb = 0;
	minus = 1;
	if ((str[nb] < '0' || str[nb] > '9') || (str[nb] == '-' && \
		str[nb + 1] == '+'))
		return (0);
	k = check_valid_simbol(str);
	if (str[k] == '-')
	{
		minus = -1;
		k++;
	}
	if (str[k] == '+')
		k++;
	while ((str[k] >= '0') && (str[k] <= '9'))
	{
		nb = nb * 10 + (str[k] - '0');
		k++;
	}
	if (check_overflow(k, minus) <= 0)
		return (check_overflow(k, minus));
	return (nb * minus);
}
