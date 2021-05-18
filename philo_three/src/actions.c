/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:38:47 by rjoella           #+#    #+#             */
/*   Updated: 2021/05/17 17:38:48 by rjoella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_three.h"

void	ft_start_think(t_philo *p)
{
	if (!p->table->who_is_die && p->count_eat != p->table->count_eat)
	{
		sem_wait(p->table->print);
		ft_print_msg(p, " \x1B[94mis thinking\033[0m\n");
		sem_post(p->table->print);
	}
}

void	ft_start_sleep(t_philo *p)
{
	if (!p->table->who_is_die && p->count_eat != p->table->count_eat)
	{
		sem_wait(p->table->print);
		ft_print_msg(p, " \x1B[93mis sleeping\033[0m\n");
		sem_post(p->table->print);
		ft_wait_time(p->table->time_to_sleep);
	}
}

void	ft_start_eat(t_philo *phil)
{
	sem_wait(phil->table->waiter);
	sem_wait(phil->table->forks);
	sem_wait(phil->table->print);
	ft_print_msg(phil, " \x1B[95mhas taken a fork LEFT\033[0m\n");
	ft_print_msg(phil, " \x1B[95mhas taken a fork RIGHT\033[0m\n");
	sem_post(phil->table->print);
	sem_wait(phil->table->forks);
	sem_post(phil->table->waiter);
	if (!phil->table->who_is_die && phil->count_eat != phil->table->count_eat)
	{
		sem_wait(phil->table->print);
		ft_print_msg(phil, " \x1B[92mis eating\033[0m\n");
		sem_post(phil->table->print);
		ft_wait_time(phil->table->time_to_eat);
		phil->when_eat = ft_calc_ts(phil->table);
		phil->count_eat++;
	}
	sem_post(phil->table->forks);
	sem_post(phil->table->forks);
}
