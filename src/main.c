/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:29:07 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/14 15:29:45 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

int	ft_start_simul(char **av)
{
	t_table	*table;
	t_philo	*philos;

	table = ft_create_table(av, -1);
	if (!table)
		return (-1);
	philos = ft_creat_philo(table);
	if (!philos)
		return (-1);
	if (ft_create_threads(table, philos) == -1)
		return (-1);
	ft_free(philos, table);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (ft_start_simul(av) == -1)
			return (-1);
	}
	else
		printf("Incorrect count args\n");
	return (0);
}
