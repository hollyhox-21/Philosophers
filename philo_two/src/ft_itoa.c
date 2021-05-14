/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:51:11 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/14 15:28:56 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

int	ft_count_char(long int n)
{
	int	i;

	i = 1;
	if (n < 0)
		n = n * -1;
	if (n > -10 && n < 10)
		return (i);
	while (i > 0)
	{
		if (n >= 10)
			n = n / 10;
		if (n < 10)
		{
			if (n == 0)
				break ;
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

char	*ft_allocation(long int n)
{
	int		i;
	char	*buf;

	i = ft_count_char(n);
	if (n < 0)
	{
		buf = malloc(i + 2);
		if (buf == NULL)
			return (NULL);
		ft_bzero(buf, (i + 2));
	}
	else
	{
		buf = malloc(i + 1);
		if (buf == NULL)
			return (NULL);
		ft_bzero(buf, (i + 1));
	}
	return (buf);
}

char	*ft_negtive(char *buf, int size, long int n)
{
	while (size > 0)
	{
		if (n > 0)
		{
			if (n < 10 && n >= 0)
			{
				*(buf + size) = n + '0';
				break ;
			}
			*(buf + size) = n % 10 + '0';
			n = n / 10;
		}
		size--;
	}
	return (buf);
}

char	*ft_positiv(char *buf, int size, int n)
{
	while (size > 0)
	{
		if (n >= 0)
		{
			*(buf + size - 1) = n % 10 + '0';
			n = n / 10;
			if (n < 10 && n >= 0)
			{
				if (size > 1)
				{
					size--;
					*(buf + size - 1) = n + '0';
				}
				n = n % 10 + '0';
				break ;
			}
		}
		size--;
	}
	return (buf);
}

char	*ft_itoa(int n)
{
	int			i;
	long int	j;
	char		*buf;

	j = n;
	buf = ft_allocation(n);
	if (buf == NULL)
		return (NULL);
	i = ft_count_char(n);
	if (n < 0)
	{
		*(buf) = '-';
		j = j * -1;
		return (ft_negtive(buf, i, j));
	}
	return (ft_positiv(buf, i, n));
}
