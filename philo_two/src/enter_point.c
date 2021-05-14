/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enter_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:05:21 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/14 15:28:49 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

void	*ft_counter_die(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	while (1)
	{
		if (ft_calc_ts(p->table) - p->when_eat > p->table->time_to_die)
			break ;
		usleep(20);
	}
	if (p->table->count_eat == -1)
		ft_print_msg(p, " \x1B[91mdied\033[0m\n");
	*p->flag_die = 1;
	return (SUCCESS);
}

void	*start_routin(void *atr)
{
	t_philo		*p;
	pthread_t	thread_die;

	p = (t_philo *)atr;
	pthread_create(&thread_die, NULL, ft_counter_die, (void *)p);
	while (!p->table->who_is_die && p->count_eat != p->table->count_eat)
	{
		ft_start_eat(p);
		ft_start_sleep(p);
		ft_start_think(p);
	}
	return (SUCCESS);
}

int	ft_create_threads(t_table *table, t_philo *philos)
{
	pthread_t	*philo;
	int			i;

	philo = (pthread_t *)malloc(sizeof(pthread_t) * table->count_philos);
	if (!philo)
		return (-1);
	i = 0;
	while (i < table->count_philos)
	{
		pthread_create(&philo[i], NULL, start_routin, (void *)&philos[i]);
		i++;
	}
	i = 0;
	while (i < table->count_philos)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	free(philo);
	return (0);
}
