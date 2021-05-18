/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:39:09 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/17 18:01:54 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_three.h"

int	ft_check_simbol(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-' || ft_isdigit(str[0]))
	{
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
				return (-1);
			i++;
		}
	}
	return (0);
}

int	ft_check_number(char *str)
{
	int	nb;

	nb = ft_atoi(str);
	if (nb <= 0)
		return (-1);
	return (0);
}

int	ft_validation(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_check_simbol(av[i]) == -1)
			return (-1);
		if (ft_check_number(av[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
