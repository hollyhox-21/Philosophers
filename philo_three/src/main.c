/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:39:04 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/17 17:54:31 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_three.h"

int	ft_start_simul(char **av)
{
	t_table	*table;
	t_philo	*philos;

	table = ft_create_table(av);
	if (!table)
		return (-1);
	philos = ft_creat_philo(table);
	if (!philos)
		return (-1);
	if (ft_create_processes(table, philos) == -1)
		return (-1);
	ft_free(philos, table);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (ft_validation(av) == -1)
		{
			printf("Invalid args\n");
			return (-1);
		}
		else if (ft_start_simul(av) == -1)
		{
			printf("FAIL PHILO!\n");
			return (-1);
		}
	}
	else
		printf("Incorrect count args\n");
	return (0);
}
