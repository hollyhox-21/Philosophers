/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:05:25 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/14 15:32:00 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

t_philo	*ft_creat_philo(t_table *table)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * table->count_philos);
	if (!philos)
		return (NULL);
	while (i < table->count_philos)
	{
		philos[i].numb = i + 1;
		philos[i].when_eat = 0;
		philos[i].count_eat = 0;
		philos[i].flag_die = &table->who_is_die;
		philos[i].table = table;
		i++;
	}
	return (philos);
}

int	ft_init_sem(t_table *t)
{
	if (sem_unlink("print") == -1)
		return (0);
	if (sem_unlink("death") == -1)
		return (0);
	if (sem_unlink("waiter") == -1)
		return (0);
	if (sem_unlink("fork") == -1)
		return (0);
	t->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	if (t->print == SEM_FAILED)
		return (0);
	t->death = sem_open("death", O_CREAT | O_EXCL, 0644, 1);
	if (t->death == SEM_FAILED)
		return (0);
	t->waiter = sem_open("waiter", O_CREAT | O_EXCL, 0644, 1);
	if (t->waiter == SEM_FAILED)
		return (0);
	t->forks = sem_open("fork", O_CREAT | O_EXCL, 0644, t->count_philos);
	if (t->forks == SEM_FAILED)
		return (0);
	return (1);
}

t_table	*ft_create_table(char **av)
{
	t_table	*t;

	t = (t_table *) malloc(sizeof(t_table) * 1);
	if (!t)
		return (NULL);
	t->count_philos = ft_atoi(av[1]);
	t->time_to_die = ft_atoi(av[2]);
	t->time_to_eat = ft_atoi(av[3]);
	t->time_to_sleep = ft_atoi(av[4]);
	gettimeofday(&t->start_t, NULL);
	t->begin_era = (t->start_t.tv_sec * 1000 + t->start_t.tv_usec / 1000);
	if (av[5])
		t->count_eat = ft_atoi(av[5]);
	else
		t->count_eat = -1;
	t->who_is_die = 0;
	if (!ft_init_sem(t))
		return (NULL);
	return (t);
}
