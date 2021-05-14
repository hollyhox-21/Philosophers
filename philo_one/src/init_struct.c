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

#include "../include/philo_one.h"

void 	ft_give_forks(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->count_philos)
	{
		if (philos[i].numb != table->count_philos)
		{
			philos[i].left_fork = &table->forks[i];
			philos[i].right_fork = &table->forks[i + 1];
		}
		else
		{
			philos[i].left_fork = &table->forks[i];
			philos[i].right_fork = &table->forks[0];
		}
		i++;
	}
}

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
		ft_give_forks(table, philos);
		i++;
	}
	return (philos);
}

t_table	*ft_create_table(char **av, int i)
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
	pthread_mutex_init(&t->print, NULL);
	pthread_mutex_init(&t->wait, NULL);
	t->forks = (pthread_mutex_t *) malloc \
		(sizeof(pthread_mutex_t) * t->count_philos);
	if (!t->forks)
		return (NULL);
	while (++i < t->count_philos)
		pthread_mutex_init(&t->forks[i], NULL);
	t->who_is_die = 0;
	return (t);
}
